#include "StdAfx.h"

#include "LFC/disasm.h"
#include "cpp_ast.h"

#include "cpp_translate.h"
#include "codegen.h"
#include "codegen_m68k.h"
//#include "../CodeComp/codegen_x86.h"

#include "codegen_ppc.h"

#include "preprocessor.h"

//#include "link.h"

#include "AOutWrite.h"
#include "COFFWrite.h"

#include <algorithm>

using namespace std;

//#include "../LFC/db.h"

//#include "../include/windows_types.h"

namespace System
{

extern Temp_temp* eax;
extern Temp_temp* edx;
extern Temp_temp* ebp;

extern Temp_temp* d0;
extern Temp_temp* d1;
extern Temp_temp* d2;
extern Temp_temp* d3;
extern Temp_temp* d4;
extern Temp_temp* d5;
extern Temp_temp* d6;
extern Temp_temp* d7;
extern Temp_temp* a0;
extern Temp_temp* a1;
extern Temp_temp* a2;
extern Temp_temp* a3;
extern Temp_temp* a4;
extern Temp_temp* a5;
extern Temp_temp* a6;
extern Temp_temp* a7;

extern Temp_temp* regs[16];

namespace cpp
{

class G_NodeList;

class G_Node
{
public:
	AS_instr* instr;

	Temp_tempList* in;
	Temp_tempList* out;

	G_Node* succ;
	//G_NodeList* succ;
};

class G_NodeList
{
public:
	G_NodeList(G_Node* _head, G_NodeList* _tail)
	{
		head = _head;
		tail = _tail;
	}

	G_Node* head;
	G_NodeList* tail;
};

Temp_tempList* find(Temp_tempList* templist, Temp_temp* temp)
{
	if (templist)
	{
		ASSERT(templist->head);
		//if (strcmp(templist->temp->name, temp->name) == 0)
		if (*templist->head == temp)
			return templist;
		else
			return find(templist->tail, temp);
	}
	else
		return NULL;
}

/*
Temp_tempList* find(Temp_tempList* templist, Temp_temp** temp)
{
	if (templist)
	{
		ASSERT(templist->temp);
		//if (strcmp(templist->temp->name, temp->name) == 0)
		if (templist->temp == temp)
			return templist;
		else
			return find(templist->tail, temp);
	}
	else
		return NULL;
}
*/

Temp_tempList* copy(Temp_tempList* a)
{
	Temp_tempList* r = NULL;

	Temp_tempList* t = a;
	while (t)
	{
		r = new Temp_tempList(t->head, r);
		t = t->tail;
	}

	return r;
}

Temp_tempList* diff(Temp_tempList* a, Temp_tempList* b)
{
//	if (a == NULL) return b;
//	if (b == NULL) return a;

	Temp_tempList* r = NULL;

	Temp_tempList* t = a;
	while (t)
	{
		if (!find(b, *t->head))
		{
			r = new Temp_tempList(t->head, r);
		}

		t = t->tail;
	}

	return r;
}

Temp_tempList* and(Temp_tempList* a, Temp_tempList* b)
{
	Temp_tempList* r = NULL;

	Temp_tempList* t = a;
	while (t)
	{
		if (find(b, *t->head))
		{
			r = new Temp_tempList(t->head, r);
		}

		t = t->tail;
	}

	return r;
}

Temp_tempList* or(Temp_tempList* a, const Temp_tempList* b)
{
	Temp_tempList* r = NULL;
	const Temp_tempList* t;
	
	t = a;
	while (t)
	{
		r = new Temp_tempList(t->head, r);
		t = t->tail;
	}

	t = b;
	while (t)
	{
		r = new Temp_tempList(t->head, r);
		t = t->tail;
	}

	// remove duplicates
	t = r;
	while (t)
	{
		Temp_tempList* prev = NULL;
		Temp_tempList* t2 = r;
		while (t2)
		{
			if (t != t2)
			{
				if (strcmp((*t->head)->name, (*t2->head)->name) == 0)
				{
					if (prev)
						prev->tail = t2->tail;
				}
			}
			prev = t2;
			t2 = t2->tail;
		}
		t = t->tail;
	}

	return r;
}

//and

class MoveList
{
public:
	MoveList(Temp_temp* _src, Temp_temp* _dst, MoveList* _tail)
	{
		src = _src;
		dst = _dst;
		tail = _tail;
	}

	Temp_temp* src;
	Temp_temp* dst;

	MoveList* tail;
};

MoveList* movelist;

G_Node* Liveness(/*Node* n,*/ AS_instrList* instrList)
{
	if (instrList->head->kind == AS_instr::I_OPER || instrList->head->kind == AS_instr::I_MOVE)
	{
		/*
		if (instrList->head->kind == AS_instr::I_OPER)
		{
			instrList->head->OPER.jumps
			*/

		G_Node* n = new G_Node;

		if (instrList->head->kind == AS_instr::I_MOVE)
		{
			movelist = new MoveList(*instrList->head->MOVE.src->head, *instrList->head->MOVE.dst->head, movelist);
		}

		n->instr = instrList->head;
		// First calculate out
		if (instrList->tail)
			n->succ = Liveness(instrList->tail);
		else
			n->succ = NULL;

		if (n->succ)
		{
			n->out = copy(n->succ->in);

			/*
			n->out = NULL;


			G_NodeList* succ = n->succ;
			while (succ)
			{
				n->out = or(n->out, succ->head->in);
				succ = succ->tail;
			}
			*/
		}
		else
			n->out = NULL;

		Temp_tempList* def = n->instr->OPER.dst;
		Temp_tempList* use = n->instr->OPER.src;

		if (def != NULL)
		{
			printf("\n");
		}
		n->in = or(use, diff(n->out, def));

		{
										Temp_tempList* tl;

										tl = n->instr->OPER.dst;
										printf("def: ");
										while (tl)
										{
											 printf("%s, ", (*tl->head)->name);
										//	if (!find(n->in, tl->temp))
										//	{
										//		printf("Usage of uninitialized variable\n");
										//	}
											tl = tl->tail;
										}

										tl = n->instr->OPER.src;
										printf("\tuse: ");
										while (tl)
										{
											 printf("%s, ", (*tl->head)->name, tl->head);
										//	if (!find(n->in, tl->temp))
										//	{
										//		printf("Usage of uninitialized variable\n");
										//	}
											tl = tl->tail;
										}

										tl = n->in;
										printf("\tlive-in: ");
										while (tl)
										{
											 printf("%s, ", (*tl->head)->name, tl->head);
										//	if (!find(n->in, tl->temp))
										//	{
										//		printf("Usage of uninitialized variable\n");
										//	}
											tl = tl->tail;
										}

										tl = n->out;
										printf("\tlive-out: ");
										while (tl)
										{
											 printf("%s, ", (*tl->head)->name, *tl->head);
										//	if (!find(n->in, tl->temp))
										//	{
										//		printf("Usage of uninitialized variable\n");
										//	}
											tl = tl->tail;
										}

										printf("\n");
										printf("\n");
		}

		return n;
	}
	else if (instrList->tail)
	{
		return Liveness(instrList->tail);
	}
	else
		return NULL;
}

struct Live_gtempList;

struct Live_gtemp
{
	Live_gtemp()
	{
		adj = NULL;
#if 0
		succ = NULL;
		pred = NULL;
#endif
		bMoveRelated = 0;
	}
	Temp_temp* temp;

	Live_gtempList* adj;

	int bMoveRelated;

#if 0
	Live_gtempList* succ;
	Live_gtempList* pred;
#endif
};

struct Live_gtempList
{
	Live_gtempList(Live_gtemp* _head, Live_gtempList* _tail)
	{
		head = _head;
		tail = _tail;
	}

	Live_gtemp* head;
	Live_gtempList* tail;
};

void printgraph(Live_gtempList* g)
{
	while (g)
	{
		//printf("%s %c - ", g->head->temp->name, g->head->bMoveRelated?'t':'f');
		printf("%s d%d a%d - ", g->head->temp->name, g->head->temp->m_dn, g->head->temp->m_an);

		Live_gtempList* adj = g->head->adj;
		while (adj)
		{
		//	printf("%s %c,", adj->head->temp->name, adj->head->bMoveRelated?'t':'f');
			printf("%s, ", adj->head->temp->name);

			adj = adj->tail;
		}
		printf("\n");


		g = g->tail;
	}
}

Live_gtempList* or(Live_gtempList* a, Live_gtempList* b)
{
	Live_gtempList* r = NULL;
	Live_gtempList* t;
	
	t = a;
	while (t)
	{
		r = new Live_gtempList(t->head, r);
		t = t->tail;
	}

	t = b;
	while (t)
	{
		r = new Live_gtempList(t->head, r);
		t = t->tail;
	}

	// remove duplicates
	t = r;
	while (t)
	{
		Live_gtempList* prev = NULL;
		Live_gtempList* t2 = r;
		while (t2)
		{
			if (t != t2)
			{
				if (strcmp(t->head->temp->name, t2->head->temp->name) == 0)
				{
					if (prev)
						prev->tail = t2->tail;
				}
			}
			prev = t2;
			t2 = t2->tail;
		}
		t = t->tail;
	}

	return r;
}

Live_gtemp* lookup(Live_gtempList* graph, Temp_temp* t)
{
	while (graph)
	{
		if (strcmp(graph->head->temp->name, t->name) == 0)
		{
			return graph->head;
		}
		graph = graph->tail;
	}
	return NULL;
}

int G_count(Live_gtempList* gl)
{
	int count = 0;
	while (gl)
	{
		count++;
		gl = gl->tail;
	}
	return count;
}

void G_addEdge(Live_gtemp* n, Live_gtemp* m)
{
	ASSERT(n);
	ASSERT(m);
	ASSERT(n != m);

	ASSERT(lookup(n->adj, m->temp) == NULL);
	ASSERT(lookup(m->adj, n->temp) == NULL);

	n->adj = new Live_gtempList(m, n->adj);

	m->adj = new Live_gtempList(n, m->adj);

#if 0
	n->succ = new Live_gtempList(m, n->succ);

	m->pred = new Live_gtempList(n, m->pred);
#endif
}

Live_gtempList* G_rmTemp(Live_gtempList* glist, Live_gtemp* n)
{
	if (glist == NULL)
		return NULL;

	if (glist->head == n)
	{
		return G_rmTemp(glist->tail, n);
	}
	else
	{
		glist->tail = G_rmTemp(glist->tail, n);
		return glist;
	}
}

void G_rmEdge(Live_gtemp* n, Live_gtemp* m)
{
	n->adj = G_rmTemp(n->adj, m);
	m->adj = G_rmTemp(m->adj, n);

#if 0
	Live_gtempList* t;

	Live_gtempList* pred;
	
	pred = NULL;
	t = n->pred;
	while (t)
	{
		if (t->head == m)
		{
			if (pred)
				pred->tail = t->tail;
			else
				n->pred = pred;
			break;
		}
		pred = t;
		t = t->tail;
	}

	pred = NULL;
	t = n->succ;
	while (t)
	{
		if (t->head == m)
		{
			if (pred)
				pred->tail = t->tail;
			else
				n->succ = pred;
			break;
		}
		pred = t;
		t = t->tail;
	}

	pred = NULL;
	t = m->pred;
	while (t)
	{
		if (t->head == n)
		{
			if (pred)
				pred->tail = t->tail;
			else
				m->pred = pred;
			break;
		}
		pred = t;
		t = t->tail;
	}

	pred = NULL;
	t = m->succ;
	while (t)
	{
		if (t->head == n)
		{
			if (pred)
				pred->tail = t->tail;
			else
				m->succ = pred;
			break;
		}
		pred = t;
		t = t->tail;
	}
#endif
}

Live_gtempList* graph;

void Interference(G_Node* n)
{
	G_Node* nl = n;
//	Node* pred = nl;
//	nl = nl->succ;
	while (nl)
	{
	//	Temp_tempList* templ = or(nl->instr->OPER.dst, nl->in);

		if (nl->instr->kind != AS_instr::I_MOVE)
		{
			Temp_tempList* tl = nl->instr->OPER.dst;
			while (tl)	// for each def
			{
				Live_gtemp* gtemp = lookup(graph, *tl->head);
				if (gtemp == NULL)
				{
					gtemp = new Live_gtemp;
					graph = new Live_gtempList(gtemp, graph);
					gtemp->temp = *tl->head;
				}

				// interfers with live-out
				Temp_tempList* tl2 = nl->out;
				while (tl2)
				{
					Live_gtemp* gtemp2 = lookup(graph, *tl2->head);
					if (gtemp2 == NULL)
					{
						gtemp2 = new Live_gtemp;
						graph = new Live_gtempList(gtemp2, graph);
						gtemp2->temp = *tl2->head;
					}

					if (gtemp != gtemp2)
					{
						if (lookup(gtemp->adj, gtemp2->temp) == NULL)	// If not already added
						{
							G_addEdge(gtemp, gtemp2);
						}
					}
					tl2 = tl2->tail;
				}

				tl = tl->tail;
			}
		}
		else
		{
			ASSERT(nl->instr->OPER.src);
			ASSERT(nl->instr->OPER.dst);
			ASSERT(nl->instr->OPER.dst->tail == NULL);
			ASSERT(nl->instr->OPER.src->tail == NULL);

			Temp_tempList* tl = nl->instr->MOVE.dst;

			ASSERT(tl->tail == NULL);

			Live_gtemp* gtemp = lookup(graph, *tl->head);
			if (gtemp == NULL)
			{
				gtemp = new Live_gtemp;
				graph = new Live_gtempList(gtemp, graph);
				gtemp->temp = *tl->head;
			}
			gtemp->bMoveRelated++;

			{
				Temp_tempList* tl = nl->instr->MOVE.src;

				Live_gtemp* gtemp = lookup(graph, *tl->head);
				if (gtemp == NULL)
				{
					gtemp = new Live_gtemp;
					graph = new Live_gtempList(gtemp, graph);
					gtemp->temp = *tl->head;
				}
				gtemp->bMoveRelated++;
			}

			// interfers with live-out

			// unless for src
			Temp_tempList* tl2 = nl->out;
			while (tl2)
			{
				Live_gtemp* gtemp2 = lookup(graph, *tl2->head);
				if (gtemp2 == NULL)
				{
					gtemp2 = new Live_gtemp;
					graph = new Live_gtempList(gtemp2, graph);
					gtemp2->temp = *tl2->head;
				}

				if (nl->instr->OPER.src == NULL || (gtemp2->temp != *nl->instr->OPER.src->head/* && strcmp(gtemp2->temp->name, nl->instr->OPER.src->temp->name) != 0*/))
				{
				//	gtemp2->bMoveRelated++;

					if (gtemp != gtemp2)
					{
						if (lookup(gtemp->adj, gtemp2->temp) == NULL)	// If not already added
						{
							G_addEdge(gtemp, gtemp2);
						}
					}
				}

				tl2 = tl2->tail;
			}
		}

		nl = nl->succ;
	}
}

//int regs[8] = {0};

void printgraph(Live_gtempList* g);

// Returns true if there are less than K nodes of significant degree
bool Conservative(Live_gtempList* g, int K)
{
	int k = 0;
	while (g)
	{
		Live_gtemp* m = g->head;
		int adjcount = G_count(m->adj);

		if (adjcount >= K)
			k++;

		g = g->tail;
	}

	return k < K;
}

stack<Live_gtemp*> gstack;

Live_gtempList* spillnodes;

T_Exp* replace(T_Exp* exp, Temp_temp* temp, T_Exp* texp)
{
	switch (exp->kind)
	{
	case T_Exp::T_TEMP:
		{
			if (*exp->temp == temp)
				return texp;
		}
		break;

	case T_Exp::T_MEM:
		{
			exp->mem.mem = replace(exp->mem.mem, temp, texp);
		}
		break;

	case T_Exp::T_UNOP:
		{
			exp->unop.exp = replace(exp->unop.exp, temp, texp);
		}
		break;

	case T_Exp::T_BINOP:
		{
			exp->binop.left = replace(exp->binop.left, temp, texp);
			exp->binop.right = replace(exp->binop.right, temp, texp);
		}
		break;

	case T_Exp::T_CONST:
		break;

	default:
		ASSERT(0);
	}

	return exp;
}

void replace(T_Stm* stm, Temp_temp* temp, T_Exp* texp)
{
	switch (stm->kind)
	{
	case T_Stm::T_MOVE:
		{
			stm->move.left = replace(stm->move.left, temp, texp);
			stm->move.right = replace(stm->move.right, temp, texp);
		}
		break;

	case T_Stm::T_EXP:
		{
			stm->exp = replace(stm->exp, temp, texp);
		}
		break;

		/*
	default:
		ASSERT(0);
		*/
	}
}

void Select(int K)
{
	Live_gtempList* g = NULL;

	while (!gstack.empty())
	{
		Live_gtemp* m = gstack.top();
		gstack.pop();

		if (g)
		{
		//	g2 = Simplify(g/*->tail*/);

			//ASSERT(!m->temp->m_precolored);

			if (!m->temp->m_precolored)
			{
				// Choose a register for m that doesn't
			// interfere with those adjacent to it

				if (m->temp->m_an == m->temp->m_dn)
				{
					int n = 0;//m->temp->m_a;
					while (1)
					{
						Live_gtempList* adj = m->adj;
						while (adj)
						{
							if (adj->head->temp->m_n == n)	// It's already used
								break;
							adj = adj->tail;
						}
						if (adj == NULL)
							break;
						n++;
					}
					if (n < K)
					{
						m->temp->m_n = n;
						printf("%s: %d\n", m->temp->name, m->temp->m_n);
					}
					else	// Actual spill
					{
						spillnodes = new Live_gtempList(m, spillnodes);

						m->temp->m_exp =
							T_Mem(
								T_BinopExp('+',
								T_Temp(&ebp),
									T_ConstExp(-4/*pDeclarator->m_offset*/)), 4/*pDeclarator->m_pType->get_sizeof()*/);

						printf("Actual spill %s\n", m->temp->name);
					}
				}
				else if (m->temp->m_an < m->temp->m_dn)
				{
					int n = 0;//m->temp->m_a;
					while (1)
					{
						Live_gtempList* adj = m->adj;
						while (adj)
						{
							if (adj->head->temp->m_n == n)	// It's already used
								break;
							adj = adj->tail;
						}
						if (adj == NULL)
							break;
						n++;
					}
					m->temp->m_n = n;
					printf("%s: %d\n", m->temp->name, m->temp->m_n);
				}
				else
				{
					int n = 8;//m->temp->m_a;
					while (1)
					{
						Live_gtempList* adj = m->adj;
						while (adj)
						{
							if (adj->head->temp->m_n == n)	// It's already used
								break;
							adj = adj->tail;
						}
						if (adj == NULL)
							break;
						n++;
					}
					m->temp->m_n = n;
					printf("%s: %d\n", m->temp->name, m->temp->m_n);
				}
			}
		}
		else
		{
			if (!m->temp->m_precolored)
			{
				m->temp->m_n = m->temp->m_a;	// Doesn't matter which we choose
			}
		//	printf("%s(%x): %d\n", m->temp->name, m->temp, m->temp->m_n);
		}

		// Reinsert m into graph
		Live_gtempList* adj = m->adj;
		while (adj)
		{
			if (lookup(adj, m->temp) == NULL)	// If not already added
			{
				adj->head->adj = new Live_gtempList(m, adj->head->adj);//, adj->head->adj = G_rmTemp(adj->head->adj, m);
			}
			adj = adj->tail;
		}
		g = new Live_gtempList(m, g);

		printgraph(g);
		printf("\n");
	}
}

Live_gtempList* Coalesce(Live_gtempList* g, AS_instrList* ilist, int K)
{
//	printgraph(g);
//	printf("\n");

	{
		MoveList* move = movelist;
		while (move)
		{

			Live_gtemp* src = lookup(g, move->src/*->getalias()*/);
			Live_gtemp* dst = lookup(g, move->dst/*->getalias()*/);
			if (src && dst)
			{
				printf("Trying to coalesce %s and %s\n", move->src->name, move->dst->name);

			//	Live_gtemp* temptemp;

				if (((src->temp->getalias()->m_dn >= src->temp->getalias()->m_an) == (dst->temp->getalias()->m_dn >= dst->temp->getalias()->m_an)) ||
					(src->temp->getalias()->m_dn == src->temp->getalias()->m_an) || dst->temp->getalias()->m_dn == dst->temp->getalias()->m_an)
				{

			//	int d = src->temp->getalias()->m_dn + dst->temp->getalias()->m_dn;
			//	int a = src->temp->getalias()->m_an + dst->temp->getalias()->m_an;

					bool bInterfers = lookup(src->adj, dst->temp) != NULL;

					if (!bInterfers)
					{
						Live_gtempList* unionadj = or(src->adj, dst->adj);

						if (Conservative(unionadj, K))
						{
						//	g2->head
							printf("Coalesce: %s,%s\n", src->temp->name, dst->temp->name);

							if (dst->temp->m_precolored)
							{
								Live_gtemp* temp = dst;
								dst = src;
								src = temp;
							}

					src->temp->getalias()->m_dn += dst->temp->getalias()->m_dn;
					src->temp->getalias()->m_an += dst->temp->getalias()->m_an;

							g = G_rmTemp(g, dst);
							{
								// Those adjacent to dst, make them adjacent to src instead

								Live_gtempList* glist2 = dst->adj;
								while (glist2)
								{
									G_rmEdge(glist2->head, dst);

									if (lookup(glist2->head->adj, src->temp) == NULL)
									{
										G_addEdge(glist2->head, src);
									}
								
									glist2 = glist2->tail;
								}
							}

							src->adj = unionadj;

							src->bMoveRelated--;
							dst->bMoveRelated--;

							ASSERT(!dst->temp->m_precolored);
							dst->temp->m_alias = src->temp;

							// join src/dst by Renaming all dst to src
							{
								Live_gtempList* glist = g;

								while (glist)
								{
									if (glist->head == dst)
									{
										ASSERT(0);
										glist->head = src;
									}
									else
									{
										Live_gtempList* glist2 = glist->head->adj;

										while (glist2)
										{
											if (glist2->head == dst)
											{
												ASSERT(0);
												glist2->head = src;
											}
											glist2 = glist2->tail;
										}
									}

									glist = glist->tail;
								}

								for (uint i = 0; i < gstack.cont.size(); ++i)
								{
									if (gstack.cont[i] == dst)
									{
										gstack.cont[i] = src;
									}
									else
									{
										Live_gtempList* glist = gstack.cont[i]->adj;

										while (glist)
										{
											if (glist->head == dst)
											{
												glist->head = src;
											}
											glist = glist->tail;
										}
									}
								}

								AS_instrList* il = ilist;

								while (il)
								{
									if (il->head->kind == AS_instr::I_MOVE)
									{
										Temp_tempList* t;

										t = il->head->MOVE.src;
										while (t)
										{
											if (*t->head == dst->temp)
											{
												*t->head = src->temp;
											}
											t = t->tail;
										}

										t = il->head->MOVE.dst;
										while (t)
										{
											if (*t->head == dst->temp)
											{
												*t->head = src->temp;
											}
											t = t->tail;
										}
									}
									else if (il->head->kind == AS_instr::I_OPER)
									{
										Temp_tempList* t;

										t = il->head->OPER.src;
										while (t)
										{
											if (*t->head == dst->temp)
											{
												*t->head = src->temp;
											}
											t = t->tail;
										}

										t = il->head->OPER.dst;
										while (t)
										{
											if (*t->head == dst->temp)
											{
												*t->head = src->temp;
											}
											t = t->tail;
										}
									}

									il = il->tail;
								}
							}

							printgraph(g);
							printf("\n");

						//	goto done_c
						}
					}
				}
			}

			move = move->tail;
		}
	}

	return g;
}

Live_gtempList* Simplify(Live_gtempList* in_g, int K)
{
	Live_gtempList* g = in_g;


	// Search the graph for the first node with less than K adjacent nodes
	while (g)
	{
		Live_gtemp* m = g->head;
		int adjcount = G_count(m->adj);
		if (!m->bMoveRelated && adjcount < K && !m->temp->m_precolored)
		{

			//if (!m->temp->precolored)
			{
				// Remove m from the adjacent nodes of m, but don't do the opposite,
				// as we need to remember the adjacent nodes of m, so we can reinsert it later
				Live_gtempList* adj = m->adj;
				while (adj)
				{
					adj->head->adj = G_rmTemp(adj->head->adj, m);
					adj = adj->tail;
				}
				in_g = G_rmTemp(in_g, m);
			}

			gstack.push(m);

			printf("Simplify\n");
			printgraph(in_g);
			printf("\n");

			// Simplify one at a time only
			break;
			/*
			printf("********************\n");
			printgraph(in_g);
			return in_g;
			*/

			/*
			// Find first non-interfering move related
			{
				Live_gtempList* g2 = g;
				while (g2)
				{
					Live_gtempList* g3 = g;
					while (g3)
					{
						if (g2 != g3)
						{
							bool bInterfers;

							if (m == g2->head)
								bInterfers = lookup(g2->head->adj, g3->head->temp) != NULL;
							else
								bInterfers = lookup(g3->head->adj, g2->head->temp) != NULL;

							if (!bInterfers)
							{
								if (Conservative(or(g2->head->adj, g3->head->adj), K))
								{
									printf("coalesce");
								}
							}
						}

						g3 = g3->tail;
					}

					g2 = g2->tail;
				}
			}
			*/

#if 0
			Live_gtempList* g2 = NULL;

			if (g)
			{
				g2 = Simplify(g/*->tail*/);

				if (!m->temp->precolored)
				{
					// Choose a register for m that doesn't
				// interfere with those adjacent to it
					int n = m->temp->m_a;
					while (1)
					{
						Live_gtempList* adj = m->adj;
						while (adj)
						{
							if (adj->head->temp->m_a+adj->head->temp->m_n == n)	// It's already used
								break;
							adj = adj->tail;
						}
						if (adj == NULL)
							break;
						n++;
					}

					m->temp->m_n = n;
					printf("%s(%x): %d\n", m->temp->name, m->temp, m->temp->m_n);
				}
			}
			else
			{
				m->temp->m_n = m->temp->m_a;	// Doesn't matter which we choose
				printf("%s(%x): %d\n", m->temp->name, m->temp, m->temp->m_n);
			}

			// Reinsert m into graph
			Live_gtempList* adj = m->adj;
			while (adj)
			{
				if (lookup(adj, m->temp) == NULL)	// If not already added
				{
					adj->head->adj = new Live_gtempList(m, adj->head->adj);//, adj->head->adj = G_rmTemp(adj->head->adj, m);
				}
				adj = adj->tail;
			}
			g2 = new Live_gtempList(m, g2);

			printgraph(g2);
			printf("\n");

			return g2;
#endif

		}

		g = g->tail;
	}

	return in_g;

	printf("********************\n");
	printgraph(in_g);
	printf("********************\n");
	// Coalesce

#if 0
	MoveList* move = movelist;
	while (move)
	{
		Live_gtemp* src = lookup(in_g, move->src);
		Live_gtemp* dst = lookup(in_g, move->dst);

		bool bInterfers = lookup(src->adj, dst->temp) != NULL;

		if (Conservative(or(src->adj, dst->adj), K))
		{
		//	g2->head
			printf("coalesce %s,%s\n", src->temp->name, dst->temp->name);

			printgraph(in_g);

		//	goto done_c
		}


		move = move->tail;
	}
#endif
	/*
			// Find first non-interfering move related
			{
				Live_gtempList* g2 = in_g;
				while (g2)
				{
					Live_gtempList* g3 = in_g;
					while (g3)
					{
						if (g2 != g3)
						{
							bool bInterfers;

							//if (m == g2->head)
								bInterfers = lookup(g2->head->adj, g3->head->temp) != NULL;
						//	else
						//		bInterfers = lookup(g3->head->adj, g2->head->temp) != NULL;

							if (!bInterfers)
							{
								if (Conservative(or(g2->head->adj, g3->head->adj), K))
								{
									g2->head
									printf("coalesce %s,%s\n", g2->head->temp->name, g3->head->temp->name);

									printgraph(in_g);

								//	goto done_c
								}
							}
						}

						g3 = g3->tail;
					}

					g2 = g2->tail;
				}
			}
			*/

//done_coalesc:
	// ??
	return in_g;
	ASSERT(0);

	/*
	printf("%s - ", m->temp->name);
	while (i)
	{
		printf("%s, ", i->head->temp->name);

		i = i->tail;
	}
	*/
}

int not_relop(int relop)
{
	switch (relop)
	{
	case '==':	return '!='; break;
	case '!=':	return '=='; break;
	case '<':	return '>='; break;
	case '>':	return '<='; break;
	case '<=':	return '>'; break;
	case '>=':	return '<'; break;

	default:
		ASSERT(0);
		return 0;
	}
}

#if 0
void ssa_rename(AS_instrList* n)
{
	map<Temp_temp**, stack<Temp_temp**> > ssa_tempStack;
	map<Temp_temp**, int> ssa_count;

	AS_instrList* slist = n;
	while (slist)
	{
		AS_instr* s = slist->head;
		
		if (s->kind == AS_instr::I_OPER || s->kind == AS_instr::I_MOVE)
		{
			if (true)	// not a ø-function
			{
				Temp_tempList* xlist = s->OPER.src;
				while (xlist)
				{
					Temp_temp** x = xlist->head;

					ASSERT(ssa_tempStack[x].size());
					Temp_temp** xi = ssa_tempStack[x].top();

				//	if (x->m_refs)
				//		*x->m_ref = xi;
					/*
					char* name_i = new char[256];
					sprintf(name_i, "%s_%d", x->name, i);
					x->name = name_i;
					*/

					xlist->head = xi;

					xlist = xlist->tail;
				}
			}

			Temp_tempList* xlist = s->OPER.dst;
			while (xlist)
			{
				Temp_temp** x = xlist->head;

				int i = ++ssa_count[x];

				Temp_temp** xi = new Temp_temp*;
				*xi = new Temp_temp;

				char* name_i = new char[256];
				sprintf(name_i, "%s_%d", (*x)->name, i);
				(*xi)->name = name_i;

				ssa_tempStack[x].push(xi);

				//x->m_alias = xi;

				xlist->head = xi;

				xlist = xlist->tail;
			}
		}

		slist = slist->tail;
	}
}
#endif

void print(T_Stm* n);

void print(T_Exp* e)
{
	if (e == NULL)
	{
		printf("(null)");
		return;
	}

	if (e->kind == T_Exp::T_ESEQ)
	{
		printf("ESEQ(");
		print(e->eseq.s);
		printf(",");
		print(e->eseq.e);
		printf(")");
	}
	else if (e->kind == T_Exp::T_CONST)
	{
		printf("CONST(%d)", e->const_int.int32Val);
	}
	else if (e->kind == T_Exp::T_MEM)
	{
		printf("MEM(");
		print(e->mem.mem);
		printf(")");
	}
	else if (e->kind == T_Exp::T_TEMP)
	{
		printf("TEMP(%s)", (*e->temp)->name);
	}
	else if (e->kind == T_Exp::T_BINOP)
	{
		printf("(");
		print(e->binop.left);
		printf("%c", e->binop.op);
		print(e->binop.right);
		printf(")");
	}
	else if (e->kind == T_Exp::T_UNOP)
	{
		printf("%c", e->unop.op);
		printf("(");
		print(e->unop.exp);
		printf(")");
	}
	else if (e->kind == T_Exp::T_CALL)
	{
		printf("CALL(");

		ArgList* args = e->call.args;
		while (args)
		{
			print(args->head);

			args = args->tail;
			if (args) printf(",");
		}

		printf(")");
	}
	else if (e->kind == T_Exp::T_NAME)
	{
		printf("NAME()");
	}
	else if (e->kind == T_Exp::T_VARIABLE)
	{
		printf("VARIABLE(%s)", e->variable);
	}
	else if (e->kind == T_Exp::T_ADDRESSOF)
	{
		printf("ADDRESSOF(");
		print(e->addressof);
		printf(")");
	}
	else if (e->kind == T_Exp::T_PHI)
	{
		printf("(");
		Temp_tempList* temps = e->phi.temps;
		while (temps)
		{
			printf("%s", (*temps->head)->name);
			temps = temps->tail;
			if (temps) printf(",");
		}
		printf(")");
	}
	else
		ASSERT(0);
}

map<T_Stm*, Temp_tempList*> stm_uses;

void print(T_Stm* s)
{
	switch (s->kind)
	{
	case T_Stm::T_LBRAC:
		{
			printf("LBRAC");
		}
		break;

	case T_Stm::T_RBRAC:
		{
			printf("RBRAC");
		}
		break;

	case T_Stm::T_SEQ:
		{
			printf("SEQ(");
			print(s->seq.left);
			printf(",");
			print(s->seq.right);
		}
		break;
		
	case T_Stm::T_MOVE:
		{
			printf("MOVE(");
			print(s->move.left);
			printf("=");
			print(s->move.right);
		}
		break;
		
	case T_Stm::T_EXP:
		{
			print(s->exp);
		}
		break;
		
	case T_Stm::T_LABEL:
		{
			printf("\n");
			printf("LABEL:\t%x", s->label);
		}
		break;
		
	case T_Stm::T_JUMP:
		{
			printf("JUMP(");
			Temp_labelList* labels = s->jump.labels;
			while (labels)
			{
				printf("%x", labels->head);
				labels = labels->tail;
				if (labels) printf(",");
			}

			printf("\n");
		}
		break;
		
	case T_Stm::T_CJUMP:
		{
			printf("CJUMP(t: %x, f: %x)", s->cjump.t, s->cjump.f);
			printf("\n");
		}
		break;
		
	default:
		;
	}

	{
		Temp_tempList* temps = stm_uses[s];

		printf(" - ");

		while (temps)
		{
			printf("%s", (*temps->head)->name);

			temps = temps->tail;
			if (temps) printf(" ");
		}
	}

	printf("\n");
}

void print(T_StmList* n)
{
	T_StmList* slist = n;
	while (slist)
	{
		T_Stm* s = slist->head;

		print(s);

		slist = slist->tail;
	}
}

#if 0
int common_subexpression_removal(T_StmList* stms)
{
	map<Temp_temp**, ULONGLONG> T1;
	map<ULONGLONG, Temp_temp**> T2;
//	map<Temp_temp**, int> N;

	int N = 0;

	int n = 0;

	T_StmList* slist = stms;
	while (slist)
	{
		T_Stm* s = slist->head;
		
		if (s->kind == T_Stm::T_MOVE)
		{
			Temp_tempListr* dst = NULL;
			ASSERT(s->move.left->kind == T_Exp::T_TEMP);

			dst = new Temp_tempListr(&s->move.left->temp, NULL);

			Temp_tempListr* src = NULL;
			if (s->move.right->kind == T_Exp::T_BINOP)
			{
				int op = s->move.right->binop.op;

				if (s->move.right->binop.left->kind == T_Exp::T_TEMP)
				{
					src = new Temp_tempListr(&s->move.right->binop.left->temp, new Temp_tempListr(&s->move.right->binop.right->temp, NULL));
				}

				ASSERT(s->move.right->binop.right->kind == T_Exp::T_TEMP);

				ULONGLONG& a = T1[*src->temp];
				ULONGLONG& b = T1[*src->tail->temp];

				T2[a] = *src->temp;
				T2[b] = *src->tail->temp;

				Temp_temp** & ast::A_op_b = T2[(a<<48) | (b<<32) | op];

				if (ast::A_op_b)
				{
					//printf("*** DELETE ***");

					n++;
					s->move.right = T_Temp(ast::A_op_b);
				}
				else
				{
					ast::A_op_b = *dst->temp;
					T1[ast::A_op_b] = ++N;
				}

				T1[*dst->temp] = ++N;
			}
			else if (s->move.right->kind == T_Exp::T_UNOP)
			{
				int op = s->move.right->unop.op;

				ASSERT(s->move.right->unop.exp->kind == T_Exp::T_TEMP);

				src = new Temp_tempListr(&s->move.right->unop.exp->temp, NULL);

				ULONGLONG& a = T1[*src->temp];
				ULONGLONG b = -1;//T1[*src->tail->temp];

				T2[a] = *src->temp;
				//T2[b] = *src->tail->temp;

				Temp_temp** & ast::A_op_b = T2[(a<<48) | (b<<32) | op];

				if (ast::A_op_b)
				{
					//printf("*** DELETE ***");

					n++;
					s->move.right = T_Temp(ast::A_op_b);
				}
				else
				{
					ast::A_op_b = *dst->temp;
					T1[ast::A_op_b] = ++N;
				}

				T1[*dst->temp] = ++N;
			}
			else if (s->move.right->kind == T_Exp::T_CONST)
			{
				T1[*dst->temp] = ++N;
			}
			else if (s->move.right->kind == T_Exp::T_TEMP)
			{
				int op = -1;
				ULONGLONG& a = T1[s->move.right->temp];
				ULONGLONG b = -1;


			//	Temp_temp** temp = T2[a];

				ULONGLONG k = T1[s->move.right->temp];

				T1[s->move.left->temp] = k;

			//	ULONGLONG Temp_temp** temp = T1[& ast::A_op_b = T2[(a<<48) | (b<<32) | op];

				/*
				if (ast::A_op_b)
				{
					//printf("*** DELETE ***");

					s->move.right = T_Temp(ast::A_op_b);
				}
				else
				{
					ast::A_op_b = *dst->temp;
					T1[ast::A_op_b] = ++N;
				}
				*/
			}
			else
				ASSERT(0);

		}

		slist = slist->tail;
	}

	return n;
}
#endif

class Operand
{
public:
	int kind;
	Temp_temp** temp;
	__int64 num;

	Operand()
	{
	}

	Operand(Temp_temp** t)
	{
		kind = 0;
		temp = t;
	}

	Operand(__int64 n)
	{
		kind = 1;
		num = n;
	}

	bool operator < (const Operand & other) const
	{
		if (kind != other.kind)
		{
			return kind < other.kind;
		}
		else if (kind == 0)
		{
			return temp < other.temp;
		}
		else
		{
			return num < other.num;
		}
	}
};

class Operation
{
public:
	Operation()
	{
	}

	Operation(const Operand & _a) : a(_a)
	{
		op = 0;
	}

	Operation(int _op, const Operand & _a, const Operand & _b) : a(_a), b(_b)
	{
		op = _op;
	}

	int op;
	Operand a;
	Operand b;

	bool operator < (const Operation & other) const
	{
		if (op != other.op) return op < other.op;
		if (a < other.a)
			return true;
		else
			return b < other.b;
	}
};

map<Temp_temp**, expRefList*> tempuses_exprefs;
map<Temp_temp**, T_StmList*> uses;
map<Temp_temp**, T_Stm*> def;

template<class l_t, class n_t> l_t * remove_node(l_t* l, n_t* n)
{
	if (l->head == n)
	{
		return l->tail;
	}
	else
	{
		ASSERT(l);

		l->tail = remove_node(l->tail, n);
		return l;
	}
}

void quadruples(T_Stm* stm);

Temp_tempList* remove_temp(Temp_tempList* l, Temp_temp** n)
{
	if (l->head == n)
	{
		return l->tail;
	}
	else
	{
		ASSERT(l);

		l->tail = remove_temp(l->tail, n);
		return l;
	}
}

int common_subexpression_removal(T_StmList* stms)
{
	map<Operation, ULONG> T1;
	map<ULONG, Temp_temp**> T2;

	int N = 0;

	int n = 0;

	N++;
	T1[Operation(&a5)] = N;
	T2[N] = &a5;

	T_StmList* sprevlist = NULL;
	T_StmList* slist = stms;
	while (slist)
	{
		T_Stm* s = slist->head;

		Temp_tempList* & stm_uselist = stm_uses[s];
		
		if (s->kind == T_Stm::T_MOVE)
		{
			printf("****\n");
			print(s);

			if (s->move.left->kind == T_Exp::T_TEMP)
			{
				Temp_tempListr* dst = NULL;
				dst = new Temp_tempListr(&s->move.left->temp, NULL);

				//Temp_tempListr* src = NULL;
				if (s->move.right->kind == T_Exp::T_BINOP)
				{
					if (s->move.right->binop.op == '*' && s->move.right->binop.right->kind == T_Exp::T_CONST &&
						s->move.right->binop.right->const_int.int32Val == 3)
					{
						printf("\nprev ***\n");
						print(s);

						s->move.right = T_BinopExp('+', T_BinopExp('<<', s->move.right->binop.left, T_ConstExp(1)), s->move.right->binop.left);
						quadruples(s);
						slist = linear(do_stm(s), slist->tail);

						printf("\ninserted ***\n");

						ASSERT(sprevlist);
						sprevlist->tail = slist;
						print(slist);

					//	T_Stm* s2 = new T_Stm;
					//	slist->tail = new T_StmList(s2, slist->tail);
					}
					else if (s->move.right->binop.op == '*' && s->move.right->binop.right->kind == T_Exp::T_CONST)
					{
						if (s->move.right->binop.right->const_int.int32Val == 2)
						{
							s->move.right = T_BinopExp('<<', s->move.right->binop.left, T_ConstExp(1));
						}
						else if (s->move.right->binop.right->const_int.int32Val == 4)
						{
							s->move.right = T_BinopExp('<<', s->move.right->binop.left, T_ConstExp(2));
						}
						else if (s->move.right->binop.right->const_int.int32Val == 8)
						{
							s->move.right = T_BinopExp('<<', s->move.right->binop.left, T_ConstExp(3));
						}
						else if (s->move.right->binop.right->const_int.int32Val == 16)
						{
							s->move.right = T_BinopExp('<<', s->move.right->binop.left, T_ConstExp(4));
						}
						else if (s->move.right->binop.right->const_int.int32Val == 32)
						{
							s->move.right = T_BinopExp('<<', s->move.right->binop.left, T_ConstExp(5));
						}
						else if (s->move.right->binop.right->const_int.int32Val == 64)
						{
							s->move.right = T_BinopExp('<<', s->move.right->binop.left, T_ConstExp(6));
						}
						else if (s->move.right->binop.right->const_int.int32Val == 128)
						{
							s->move.right = T_BinopExp('<<', s->move.right->binop.left, T_ConstExp(7));
						}
						else if (s->move.right->binop.right->const_int.int32Val == 256)
						{
							s->move.right = T_BinopExp('<<', s->move.right->binop.left, T_ConstExp(8));
						}
						else if (s->move.right->binop.right->const_int.int32Val == (1<<9))
						{
							s->move.right = T_BinopExp('<<', s->move.right->binop.left, T_ConstExp(9));
						}
						else if (s->move.right->binop.right->const_int.int32Val == (1<<10))
						{
							s->move.right = T_BinopExp('<<', s->move.right->binop.left, T_ConstExp(10));
						}
						else if (s->move.right->binop.right->const_int.int32Val == (1<<11))
						{
							s->move.right = T_BinopExp('<<', s->move.right->binop.left, T_ConstExp(11));
						}
						else if (s->move.right->binop.right->const_int.int32Val == (1<<12))
						{
							s->move.right = T_BinopExp('<<', s->move.right->binop.left, T_ConstExp(12));
						}
						else if (s->move.right->binop.right->const_int.int32Val == (1<<13))
						{
							s->move.right = T_BinopExp('<<', s->move.right->binop.left, T_ConstExp(13));
						}
						else if (s->move.right->binop.right->const_int.int32Val == (1<<14))
						{
							s->move.right = T_BinopExp('<<', s->move.right->binop.left, T_ConstExp(14));
						}
						else if (s->move.right->binop.right->const_int.int32Val == (1<<15))
						{
							s->move.right = T_BinopExp('<<', s->move.right->binop.left, T_ConstExp(15));
						}
						else if (s->move.right->binop.right->const_int.int32Val == (1<<16))
						{
							s->move.right = T_BinopExp('<<', s->move.right->binop.left, T_ConstExp(16));
						}
					}

					int op = s->move.right->binop.op;

					ULONG a;
					ULONG b;

					if (s->move.right->binop.left->kind == T_Exp::T_TEMP)
					{
						a = T1[Operation(s->move.right->binop.left->temp)];
						//src = new Temp_tempListr(&s->move.right->binop.left->temp, new Temp_tempListr(&s->move.right->binop.right->temp, NULL));
					}
					else if (s->move.right->binop.left->kind == T_Exp::T_CONST)
					{
						a = T1[Operation(s->move.right->binop.left->const_int.int32Val)];

						if (a == 0)
						{
							N++;
							a = N;
							T1[Operation(s->move.right->binop.left->const_int.int32Val)] = a;
						}
					}
					else if (s->move.right->binop.left->kind == T_Exp::T_MEM)
					{
						N++;

						T1[Operation(s->move.right->binop.left->mem.mem->temp)] = N;
						T2[++N] = *dst->temp;
					}
					else
						ASSERT(0);

					if (s->move.right->binop.right->kind == T_Exp::T_TEMP)
					{
						b = T1[Operation(s->move.right->binop.right->temp)];
						//src = new Temp_tempListr(&s->move.right->binop.left->temp, new Temp_tempListr(&s->move.right->binop.right->temp, NULL));
					}
					else if (s->move.right->binop.right->kind == T_Exp::T_CONST)
					{
						b = T1[Operation(s->move.right->binop.right->const_int.int32Val)];

						if (b == 0)
						{
							N++;
							b = N;
							T1[Operation(s->move.right->binop.right->const_int.int32Val)] = b;
						}
					}
					else
						ASSERT(0);

					/*
					T2[a] = *src->temp;
					T2[b] = *src->tail->temp;
					*/

					ASSERT(a);
					ASSERT(b);

					ULONG &a_op_b = T1[Operation(op, a, b)];

					if (a_op_b)
					{
						//printf("*** DELETE ***");

						Temp_temp** t = T2[a_op_b];

						if (s->move.right->binop.left->kind == T_Exp::T_TEMP)
						{
							uses[s->move.right->binop.left->temp] = remove_node(uses[s->move.right->binop.left->temp], s);
							stm_uselist = remove_temp(stm_uselist, s->move.right->binop.left->temp);
						}

						if (s->move.right->binop.right->kind == T_Exp::T_TEMP)
						{
							uses[s->move.right->binop.right->temp] = remove_node(uses[s->move.right->binop.right->temp], s);
							stm_uselist = remove_temp(stm_uselist, s->move.right->binop.right->temp);
						}

						T_Stm* defsite = def[t];

						uses[t] = new T_StmList(s, uses[t]);
						stm_uselist = new Temp_tempList(t, stm_uselist);

						/*
						Temp_tempList* stm_uselist2 = stm_uses[defsite];
						while (stm_uselist2)
						{
							uses[stm_uselist2->temp] = new T_StmList(s, uses[stm_uselist2->temp]);
							stm_uselist = new Temp_tempList(stm_uselist2->temp, stm_uselist);

							stm_uselist2 = stm_uselist2->tail;
						}
						*/

						n++;
						s->move.right = T_Temp(t/*T2[ast::A_op_b]*/);
					}
					else
					{
						N++;
						a_op_b = N;//*dst->temp;
					//	T1[*dst->temp] = Operation(ast::A_op_b);//++N;
					//	T1[ast::A_op_b] 

					}

						T1[Operation(*dst->temp)] = N;
						T2[a_op_b] = *dst->temp;

					//T1[Operation(*dst->temp)] = ++N;
				}
				else if (s->move.right->kind == T_Exp::T_UNOP)
				{
	#if 0
					int op = s->move.right->unop.op;

					ASSERT(s->move.right->unop.exp->kind == T_Exp::T_TEMP);

					src = new Temp_tempListr(&s->move.right->unop.exp->temp, NULL);

					ULONGLONG& a = T1[*src->temp];
					ULONGLONG b = -1;//T1[*src->tail->temp];

					T2[a] = *src->temp;
					//T2[b] = *src->tail->temp;

					Temp_temp** & ast::A_op_b = T2[(a<<48) | (b<<32) | op];

					if (ast::A_op_b)
					{
						//printf("*** DELETE ***");

						n++;
						s->move.right = T_Temp(ast::A_op_b);
					}
					else
					{
						ast::A_op_b = *dst->temp;
						T1[ast::A_op_b] = ++N;
					}

					T1[Operation(*dst->temp)] = ++N;
	#endif
				}
				else if (s->move.right->kind == T_Exp::T_CONST)
				{
					N++;
				//	T1[Operation(s->move.right->const_int.int32)] = Operation(s->move.right->const_int.int32);
					T1[Operation(s->move.right->const_int.int32Val)] = N;
					T1[Operation(*dst->temp)] = N;
					T2[N] = *dst->temp;//
				}
				else if (s->move.right->kind == T_Exp::T_TEMP)
				{
					//T1[Operation(*dst->temp)] = s->move.right->temp;//Operation(s->move.right->temp);
					N++;

					T1[Operation(s->move.right->temp)] = N;
					T1[Operation(*dst->temp)] = N;
					T2[N] = *dst->temp;
				}
				else if (s->move.right->kind == T_Exp::T_MEM)
				{
					//T1[Operation(*dst->temp)] = s->move.right->temp;//Operation(s->move.right->temp);
					N++;

					if (s->move.right->mem.mem->kind == T_Exp::T_TEMP)
					{
						T1[Operation(s->move.right->mem.mem->temp)] = N;
						T1[Operation(*dst->temp)] = N;
						T2[N] = *dst->temp;
					}
				}
				else if (s->move.right->kind == T_Exp::T_ADDRESSOF)
				{
					/*
					//T1[Operation(*dst->temp)] = s->move.right->temp;//Operation(s->move.right->temp);
					N++;

					if (s->move.right->addressof->kind == T_Exp::T_TEMP)
					{
						T1[Operation(s->move.right->addressof->temp)] = N;
						T1[Operation(*dst->temp)] = N;
						T2[N] = *dst->temp;
					}
					else
						ASSERT(0);
						*/
				}
				else
					ASSERT(0);
			}
		}
		else if (s->kind == T_Stm::T_EXP)
		{
			T_Exp* e = s->exp;
			if (e->kind == T_Exp::T_CALL)
			{
				ArgList* args = e->call.args;
			}
			else
				ASSERT(0);
		}

		sprevlist = slist;
		slist = slist->tail;
	}

	return n;
}

#if 0
int unfolding(T_StmList* stms)
{
	map<Operation, ULONG> T1;
	map<ULONG, Operation> T2;

	int N = 0;

	int n = 0;

	T_StmList* slist = stms;
	while (slist)
	{
		T_Stm* s = slist->head;
		
		if (s->kind == T_Stm::T_MOVE)
		{
			Temp_tempListr* dst = NULL;
			ASSERT(s->move.left->kind == T_Exp::T_TEMP);

			dst = new Temp_tempListr(&s->move.left->temp, NULL);

			//Temp_tempListr* src = NULL;
			if (s->move.right->kind == T_Exp::T_BINOP)
			{
				int op = s->move.right->binop.op;

				ULONG a;
				ULONG b;

				if (s->move.right->binop.left->kind == T_Exp::T_TEMP)
				{
					a = T1[Operation(s->move.right->binop.left->temp)];
					//src = new Temp_tempListr(&s->move.right->binop.left->temp, new Temp_tempListr(&s->move.right->binop.right->temp, NULL));
				}
				else if (s->move.right->binop.left->kind == T_Exp::T_CONST)
				{
					a = T1[Operation(s->move.right->binop.left->const_int.int32)];

					if (a == 0)
					{
						N++;
						a = N;
						T1[Operation(s->move.right->binop.left->const_int.int32)] = a;
					}
				}
				else
					ASSERT(0);

				if (s->move.right->binop.right->kind == T_Exp::T_TEMP)
				{
					b = T1[Operation(s->move.right->binop.right->temp)];
					//src = new Temp_tempListr(&s->move.right->binop.left->temp, new Temp_tempListr(&s->move.right->binop.right->temp, NULL));
				}
				else if (s->move.right->binop.right->kind == T_Exp::T_CONST)
				{
					b = T1[Operation(s->move.right->binop.right->const_int.int32)];

					if (b == 0)
					{
						N++;
						b = N;
						T1[Operation(s->move.right->binop.right->const_int.int32)] = b;
					}
				}
				else
					ASSERT(0);

				if (s->move.right->binop.right->kind == T_Exp::T_CONST)
				{
					def = 
				}

				/*
				T2[a] = *src->temp;
				T2[b] = *src->tail->temp;
				*/

				ULONG &ast::A_op_b = T1[Operation(op, a, b)];

				if (ast::A_op_b)
				{
					//printf("*** DELETE ***");

					n++;
				//	s->move.right = T_Temp(T2[ast::A_op_b]);
				}
				else
				{
					N++;
					ast::A_op_b = N;//*dst->temp;
				//	T1[*dst->temp] = Operation(ast::A_op_b);//++N;
				//	T1[ast::A_op_b] 
				}

				T2[ast::A_op_b] = Operation(op, a, b);//*dst->temp;
				//T1[Operation(*dst->temp)] = ++N;
			}
			else if (s->move.right->kind == T_Exp::T_UNOP)
			{
#if 0
				int op = s->move.right->unop.op;

				ASSERT(s->move.right->unop.exp->kind == T_Exp::T_TEMP);

				src = new Temp_tempListr(&s->move.right->unop.exp->temp, NULL);

				ULONGLONG& a = T1[*src->temp];
				ULONGLONG b = -1;//T1[*src->tail->temp];

				T2[a] = *src->temp;
				//T2[b] = *src->tail->temp;

				Temp_temp** & ast::A_op_b = T2[(a<<48) | (b<<32) | op];

				if (ast::A_op_b)
				{
					//printf("*** DELETE ***");

					n++;
					s->move.right = T_Temp(ast::A_op_b);
				}
				else
				{
					ast::A_op_b = *dst->temp;
					T1[ast::A_op_b] = ++N;
				}

				T1[Operation(*dst->temp)] = ++N;
#endif
			}
			else if (s->move.right->kind == T_Exp::T_CONST)
			{
				N++;
			//	T1[Operation(s->move.right->const_int.int32)] = Operation(s->move.right->const_int.int32);
				T1[Operation(s->move.right->const_int.int32)] = N;
				T1[Operation(*dst->temp)] = N;
				T2[N] = Operation(*dst->temp);//
			}
			else if (s->move.right->kind == T_Exp::T_TEMP)
			{
				//T1[Operation(*dst->temp)] = s->move.right->temp;//Operation(s->move.right->temp);
				N++;

				T1[Operation(s->move.right->temp)] = N;
				T2[++N] = Operation(*dst->temp);
#if 0
				int op = -1;
				ULONGLONG& a = T1[s->move.right->temp];
				ULONGLONG b = -1;


			//	Temp_temp** temp = T2[a];

				ULONGLONG k = T1[s->move.right->temp];

				T1[s->move.left->temp] = k;

			//	ULONGLONG Temp_temp** temp = T1[& ast::A_op_b = T2[(a<<48) | (b<<32) | op];

				/*
				if (ast::A_op_b)
				{
					//printf("*** DELETE ***");

					s->move.right = T_Temp(ast::A_op_b);
				}
				else
				{
					ast::A_op_b = *dst->temp;
					T1[ast::A_op_b] = ++N;
				}
				*/
#endif
			}
			else
				ASSERT(0);

		}

		slist = slist->tail;
	}

	return n;
}
#endif

int remove_dead_code(T_StmList* & n)//, T_StmList** new_list)
{
	map<Temp_temp**, T_Stm*> ssa_tempStack;
	//map<Temp_temp**, int> ssa_count;

	int changed = 0;

	T_StmList* slist = n;
	T_StmList* prev = NULL;
	while (slist)
	{
		T_Stm* s = slist->head;

		Temp_tempList* stm_use_list = stm_uses[s];
		
		if (s->kind == T_Stm::T_MOVE)
		{
			if (s->move.left->kind == T_Exp::T_TEMP)
			{
				T_StmList* & u = uses[s->move.left->temp];
				// If the def of this statement has 0 uses
				if (u == NULL)
				{
					// Remove this statement

					changed++;

					if (prev)
						prev->tail = slist->tail;
					else
						n = slist->tail;

					ASSERT(def[s->move.left->temp] == s);
					def[s->move.left->temp] = NULL;

					while (stm_use_list)
					{
						Temp_temp** temp = stm_use_list->head;

						T_Stm* defsite = def[temp];
						if (defsite)
						{
							T_StmList* & u = uses[defsite->move.left->temp];
							u = remove_node(u, s);
						}

						stm_use_list = stm_use_list->tail;
					}
				}
				else
				{
					prev = slist;
				}
			}
			else
			{
				prev = slist;
			}
		}
		else
		{
			prev = slist;
		}

		slist = slist->tail;
	}

	return changed;
}

int const_copy_propagation(T_StmList* n)
{
	//map<Temp_temp**, T_Stm*> ssa_tempStack;
	//map<Temp_temp**, int> ssa_count;

	int changed = 0;

	T_StmList* slist = n;
	while (slist)
	{
		T_Stm* s = slist->head;

		Temp_tempList* & stm_use_list = stm_uses[s];
		
		if (s->kind == T_Stm::T_MOVE)
		{
			Temp_tempListr* dst = NULL;
			//if (s->move.left->kind == T_Exp::T_TEMP)
			//dst = new Temp_tempListr(&s->move.left->temp, NULL);

			Temp_tempListr* src = NULL;
			if (s->move.right->kind == T_Exp::T_BINOP)
			{
				// constant propagation

				if (s->move.right->binop.left->kind == T_Exp::T_TEMP)
				{
					T_Stm* defsite = def[s->move.right->binop.left->temp];

					if (defsite)
					{
						if (defsite->move.right->kind == T_Exp::T_CONST)	// constant propagation
						{
							stm_use_list = remove_temp(stm_use_list, s->move.right->binop.left->temp);

							T_StmList* & u = uses[defsite->move.left->temp];
							u = remove_node(u, s);

							s->move.right->binop.left = T_ConstExp(defsite->move.right->const_int.int32Val);
							changed++;
						}
						else if (defsite->move.right->kind == T_Exp::T_TEMP)	// copy propagation
						{
							//T_StmList* & u = uses[defsite->move.left->temp];
						
							stm_use_list = remove_temp(stm_use_list, s->move.right->binop.left->temp);
							//u = remove_node(u, s);
							uses[s->move.right->binop.left->temp] = remove_node(uses[s->move.right->binop.left->temp], s);

							{
							uses[defsite->move.right->temp] = new T_StmList(s, uses[defsite->move.right->temp]);
							stm_use_list = new Temp_tempList(defsite->move.right->temp, stm_use_list);
							}

							s->move.right->binop.left = T_Temp(defsite->move.right->temp);
							changed++;
						}
					}
				}

				if (s->move.right->binop.right->kind == T_Exp::T_TEMP)
				{
					T_Stm* defsite = def[s->move.right->binop.right->temp];

					if (defsite)
					{
						if (defsite->move.right->kind == T_Exp::T_CONST)	// constant propagation
						{
							stm_use_list = remove_temp(stm_use_list, s->move.right->binop.right->temp);

							T_StmList* & u = uses[defsite->move.left->temp];
							u = remove_node(u, s);

							s->move.right->binop.right = T_ConstExp(defsite->move.right->const_int.int32Val);
							changed++;
						}
						else if (defsite->move.right->kind == T_Exp::T_TEMP)	// copy propagation
						{
							stm_use_list = remove_temp(stm_use_list, s->move.right->binop.right->temp);

							//T_StmList* & u = uses[defsite->move.left->temp];
							//u = remove_node(u, s);
							uses[s->move.right->binop.right->temp] = remove_node(uses[s->move.right->binop.right->temp], s);

							{
							uses[defsite->move.right->temp] = new T_StmList(s, uses[defsite->move.right->temp]);
							stm_use_list = new Temp_tempList(defsite->move.right->temp, stm_use_list);
							}

							s->move.right->binop.right = T_Temp(defsite->move.right->temp);
							changed++;
						}
					}
				}

				// constant folding
				// convert (const0 op const0) -> const1
				if (s->move.right->binop.left->kind == T_Exp::T_CONST_INT32 &&
					s->move.right->binop.right->kind == T_Exp::T_CONST_INT32)
				{
					changed++;

					int32 value;

					switch (s->move.right->binop.op)
					{
					case '+':
						{
							value = s->move.right->binop.left->const_int.int32Val + s->move.right->binop.right->const_int.int32Val;
						}
						break;
						
					case '-':
						{
							value = s->move.right->binop.left->const_int.int32Val - s->move.right->binop.right->const_int.int32Val;
						}
						break;
						
					case '*':
						{
							value = s->move.right->binop.left->const_int.int32Val * s->move.right->binop.right->const_int.int32Val;
						}
						break;
						
					case '/':
						{
							value = s->move.right->binop.left->const_int.int32Val / s->move.right->binop.right->const_int.int32Val;
						}
						break;
						
					case '%':
						{
							value = s->move.right->binop.left->const_int.int32Val % s->move.right->binop.right->const_int.int32Val;
						}
						break;

					case '|':
						{
							value = s->move.right->binop.left->const_int.int32Val | s->move.right->binop.right->const_int.int32Val;
						}
						break;

					case '&':
						{
							value = s->move.right->binop.left->const_int.int32Val & s->move.right->binop.right->const_int.int32Val;
						}
						break;

					case '^':
						{
							value = s->move.right->binop.left->const_int.int32Val ^ s->move.right->binop.right->const_int.int32Val;
						}
						break;
						
					case '<<':
						{
							value = s->move.right->binop.left->const_int.int32Val << s->move.right->binop.right->const_int.int32Val;
						}
						break;
						
					default:
						ASSERT(0);
					}

					s->move.right = T_ConstExp(value);
				}
				else if (s->move.right->binop.left->kind == T_Exp::T_CONST_INT64 &&
					s->move.right->binop.right->kind == T_Exp::T_CONST_INT64)
				{
					changed++;

					int64 value;

					switch (s->move.right->binop.op)
					{
					case '+':
						{
							value = s->move.right->binop.left->const_int.int64Val + s->move.right->binop.right->const_int.int64Val;
						}
						break;
						
					case '-':
						{
							value = s->move.right->binop.left->const_int.int64Val - s->move.right->binop.right->const_int.int64Val;
						}
						break;
						
					case '*':
						{
							value = s->move.right->binop.left->const_int.int64Val * s->move.right->binop.right->const_int.int64Val;
						}
						break;
						
					case '/':
						{
							value = s->move.right->binop.left->const_int.int64Val / s->move.right->binop.right->const_int.int64Val;
						}
						break;
						
					case '%':
						{
							value = s->move.right->binop.left->const_int.int64Val % s->move.right->binop.right->const_int.int64Val;
						}
						break;

					case '|':
						{
							value = s->move.right->binop.left->const_int.int64Val | s->move.right->binop.right->const_int.int64Val;
						}
						break;

					case '&':
						{
							value = s->move.right->binop.left->const_int.int64Val & s->move.right->binop.right->const_int.int64Val;
						}
						break;

					case '^':
						{
							value = s->move.right->binop.left->const_int.int64Val ^ s->move.right->binop.right->const_int.int64Val;
						}
						break;
						
					case '<<':
						{
							value = s->move.right->binop.left->const_int.int64Val << s->move.right->binop.right->const_int.int64Val;
						}
						break;
						
					default:
						ASSERT(0);
					}

					s->move.right = T_Const64Exp(value);
				}
			}
#if 0
				else
				// convert (const0 (+)/(*) x) -> (x (+)/(*) const0)
				if ((s->move.right->binop.op == '+' || s->move.right->binop.op == '*') &&
					s->move.right->binop.left->kind == T_Exp::T_CONST &&
					s->move.right->binop.right->kind == T_Exp::T_TEMP)
				{
					T_Exp* t = s->move.right->binop.left;
					s->move.right->binop.left = s->move.right->binop.right;
					s->move.right->binop.right = t;
				}

			if (s->move.right->kind == T_Exp::T_BINOP)
			{
				if (s->move.right->binop.left->kind == T_Exp::T_TEMP)
				{
					//src = new Temp_tempListr(&s->move.right->binop.left->temp, NULL);

					T_Stm* defsite = ssa_tempStack[s->move.right->binop.left->temp];

					if (defsite)
					{
						T_Exp* defexp = defsite->move.right;

						if (defexp->kind == T_Exp::T_BINOP)
						{
							// unfold

						//	T_StmList* u = uses[defsite->move.left->temp];
						//	if (u && u->tail == NULL)
							{
								s->move.right->binop.left = T_BinopExp(defexp->binop.op, defexp->binop.left, defexp->binop.right);
							}

							/*
							// convert (x + y) + const0 -> (x + const0) + y
							if (s->move.right->binop.op == '+' &&
								s->move.right->binop.right->kind == T_Exp::T_CONST &&

								s->move.right->binop.left->kind == T_Exp::T_BINOP &&
								s->move.right->binop.left->binop.op == '+' &&
								s->move.right->binop.left->binop.right->kind == T_Exp::T_TEMP)
							{
								T_Exp* t = s->move.right->binop.left->binop.right;
								s->move.right->binop.left->binop.right = s->move.right->binop.right;
								s->move.right->binop.right = t;
							}

							// convert (x + const0) + const1 -> x + (const0 + const1)
							if (s->move.right->binop.op == '+')
							{
								if (s->move.right->binop.right->kind == T_Exp::T_CONST)
								{
									if (s->move.right->binop.left->kind == T_Exp::T_BINOP)
									{
										if (s->move.right->binop.left->binop.right->kind == T_Exp::T_CONST)
										{
											s->move.right = T_BinopExp(
												'+',
												s->move.right->binop.left->binop.left,
												T_ConstExp(s->move.right->binop.left->binop.right->const_int.int32 + s->move.right->binop.right->const_int.int32));
										}
									}
								}
							}
							else if (s->move.right->binop.op == '-')
							{
								if (s->move.right->binop.right->kind == T_Exp::T_CONST)
								{
									if (s->move.right->binop.left->binop.right->kind == T_Exp::T_CONST)
									{
										s->move.right = T_BinopExp(
											'+',
											s->move.right->binop.left->binop.left,
											T_ConstExp(s->move.right->binop.left->binop.right->const_int.int32 - s->move.right->binop.right->const_int.int32));
									}
								}
							}
							*/
						}

						// convert (x + const0) + const1 -> x + (const0 + const1)
						if (s->move.right->binop.op == '+')
						{
							if (s->move.right->binop.right->kind == T_Exp::T_CONST)
							{
								if (s->move.right->binop.left->kind == T_Exp::T_BINOP)
								{
									if (s->move.right->binop.left->binop.right->kind == T_Exp::T_CONST)
									{
										s->move.right = T_BinopExp(
											'+',
											s->move.right->binop.left->binop.left,
											T_ConstExp(s->move.right->binop.left->binop.right->const_int.int32 + s->move.right->binop.right->const_int.int32));
									}
								}
							}
						}
					}
				}
				else
					ASSERT(0);

				if (s->move.right->binop.right->kind == T_Exp::T_TEMP)
				{
					T_Stm* defsite = ssa_tempStack[s->move.right->binop.right->temp];

					T_Exp* defexp = defsite->move.right;

					if (defexp->kind == T_Exp::T_BINOP)
					{
						T_StmList* u = uses[defsite->move.left->temp];
						if (u && u->tail == NULL)
						{
							s->move.right->binop.right = T_BinopExp(defexp->binop.op, defexp->binop.left, defexp->binop.right);
						}
					}
				}

				// (x + const0) + (y + const1) -> (x + (const0+const1)) + y
				if (s->move.right->binop.op == '+' &&

					s->move.right->binop.left->kind == T_Exp::T_BINOP &&
					s->move.right->binop.left->binop.right->kind == T_Exp::T_CONST &&

					s->move.right->binop.right->kind == T_Exp::T_BINOP &&
					s->move.right->binop.right->binop.right->kind == T_Exp::T_CONST)
				{
					s->move.right =
						T_BinopExp('+',

							T_BinopExp('+',
									s->move.right->binop.left->binop.left,
									T_ConstExp(s->move.right->binop.left->binop.right->const_int.int32 + s->move.right->binop.right->binop.right->const_int.int32)
							),

							s->move.right->binop.right->binop.left);
				}

				/*
				if (s->move.right->binop.right->kind == T_Exp::T_TEMP)
				{
				//	src = new Temp_tempListr(&s->move.right->binop.right->temp, src);

					T_Exp* defsite = ssa_tempStack[s->move.right->binop.right->temp]->move.right;
					if (defsite->kind == T_Exp::T_BINOP)
					{
						s->move.right->binop.right = T_BinopExp(defsite->binop.op, defsite->binop.left, defsite->binop.right);
					}
				}
				*/
			}
			/*
			else if (s->move.right->kind == T_Exp::T_UNOP)
			{
				ASSERT(s->move.right->unop.exp->kind == T_Exp::T_TEMP);

				src = new Temp_tempListr(&s->move.right->unop.exp->temp, NULL);
			}
			*/
			else if (s->move.right->kind == T_Exp::T_CONST)
			{
			}
			else if (s->move.right->kind == T_Exp::T_TEMP)
			{
				T_Stm* defsite = ssa_tempStack[s->move.right->temp];

				T_Exp* defexp = defsite->move.right;

				if (defexp->kind == T_Exp::T_BINOP)
				{
					T_StmList* u = uses[defsite->move.left->temp];
					if (u && u->tail == NULL)
					{
						s->move.right = T_BinopExp(defexp->binop.op, defexp->binop.left, defexp->binop.right);
					}
				}
			}
			else if (s->move.right->kind == T_Exp::T_MEM)
			{
				T_Stm* defsite = ssa_tempStack[s->move.right->mem.mem->temp];

				if (defsite)
				{
					T_Exp* defexp = defsite->move.right;

					if (defexp->kind == T_Exp::T_BINOP)
					{
						T_StmList* u = uses[defsite->move.left->temp];
						if (u && u->tail == NULL)
						{
							s->move.right->mem.mem = T_BinopExp(defexp->binop.op, defexp->binop.left, defexp->binop.right);
						}
					}
				}
			}

			/*
			if (true)	// not a ø-function
			{
				Temp_tempListr* xlist = src;
				while (xlist)
				{
					Temp_temp** x = *xlist->temp;

					printf("use: %p\n", x);

					//ASSERT(ssa_tempStack[x].size());
				//	Temp_temp** xi = ssa_tempStack[x];//.top();
				

				//	*xlist->temp = xi;

					xlist = xlist->tail;
				}
			}
			*/
#endif
#if 0
			Temp_tempListr* xlist = dst;
			while (xlist)
			{
				Temp_temp** x = *xlist->temp;

		//		printf("def: %p\n", x);

		//		int i = ++ssa_count[x];

				/*
				Temp_temp** xi = new Temp_temp*;
				*xi = new Temp_temp;

				char* name_i = new char[256];
				sprintf(name_i, "%s_%d", (*x)->name, i);
				(*xi)->name = name_i;
				*/

				ssa_tempStack[x] = s;//->move.right;//.push(xi);

			//	*xlist->temp = xi;

				xlist = xlist->tail;
			}
#endif
		}
		else if (s->kind == T_Stm::T_EXP)
		{
			T_Exp* e = s->exp;
			if (e->kind == T_Exp::T_CALL)
			{
				ArgList* args = e->call.args;
				while (args)
				{
					if (args->head->kind == T_Exp::T_TEMP)
					{
						T_Stm* defsite = def[args->head->temp];

						T_Exp* defexp = defsite->move.right;

						if (defexp->kind == T_Exp::T_CONST)	// constant propagation
						{
							stm_use_list = remove_temp(stm_use_list, args->head->temp);

							T_StmList* & u = uses[defsite->move.left->temp];
							u = remove_node(u, s);

							args->head = T_ConstExp(defsite->move.right->const_int.int32Val);
							changed++;
						}
						else if (defexp->kind == T_Exp::T_TEMP)	// copy propagation
						{
							stm_use_list = remove_temp(stm_use_list, args->head->temp);
							uses[defsite->move.left->temp] = remove_node(uses[defsite->move.left->temp], s);

							{
							uses[defsite->move.right->temp] = new T_StmList(s, uses[defsite->move.right->temp]);
							stm_use_list = new Temp_tempList(defsite->move.right->temp, stm_use_list);
							}

							args->head = T_Temp(defsite->move.right->temp);
							changed++;
						}
					}
					else if (args->head->kind == T_Exp::T_CONST)
					{
					}
					else if (args->head->kind == T_Exp::T_NAME)
					{
					}
					else
						ASSERT(0);

					args = args->tail;
				}
			}
			else
				ASSERT(0);
		}

		slist = slist->tail;
	}

	return changed;
}

int unfold(T_Stm* s, T_Exp* & e)
{
	int changed = 0;

	Temp_tempList* & stm_uselist = stm_uses[s];

	if (e->kind == T_Exp::T_BINOP)
	{
		changed += unfold(s, e->binop.left);
		changed += unfold(s, e->binop.right);

#if 0
		if (e->binop.left->kind == T_Exp::T_TEMP)
		{
			//src = new Temp_tempListr(&s->move.right->binop.left->temp, NULL);

			T_Stm* defsite = def[e->binop.left->temp];

			if (defsite)
			{
				T_Exp* defexp = defsite->move.right;

				if (defexp->kind == T_Exp::T_BINOP)
				{
					//unfolding(s->move.right->binop.left

					uses[defsite->move.left->temp] = remove_node(uses[defsite->move.left->temp], s);
					stm_uselist = remove_temp(stm_uselist, defsite->move.left->temp);

					// unfold

				//	T_StmList* u = uses[defsite->move.left->temp];
				//	if (u && u->tail == NULL)
					{
						/*
						if (defexp->binop.left->kind == T_Exp::T_TEMP)
						{
							stm_uselist = new Temp_tempList(defexp->binop.left->temp, stm_uselist);
							uses[defexp->binop.left->temp] = new T_StmList(s, uses[defexp->binop.left->temp]);
						}
						*/
						{
							Temp_tempList* stm_uselist2 = stm_uses[defsite];
							while (stm_uselist2)
							{
								uses[stm_uselist2->temp] = new T_StmList(s, uses[stm_uselist2->temp]);
								stm_uselist = new Temp_tempList(stm_uselist2->temp, stm_uselist);

								stm_uselist2 = stm_uselist2->tail;
							}
						}

						/*
						if (defexp->binop.right->kind == T_Exp::T_TEMP)
						{
							stm_uselist = new Temp_tempList(defexp->binop.right->temp, stm_uselist);
							uses[defexp->binop.right->temp] = new T_StmList(s, uses[defexp->binop.right->temp]);
						}
						*/
						/*
						{
							Temp_tempList* stm_uselist2 = stm_uses[defsite];
							while (stm_uselist2)
							{
								uses[stm_uselist2->temp] = new T_StmList(s, uses[stm_uselist2->temp]);
								stm_uselist = new Temp_tempList(stm_uselist2->temp, stm_uselist);

								stm_uselist2 = stm_uselist2->tail;
							}
						}
						*/

						s->move.right->binop.left = T_BinopExp(defexp->binop.op, defexp->binop.left, defexp->binop.right);
						changed++;

						printf("***\n");
						print(s);
						printf("\n");
					}

					/*
					// convert (x + y) + const0 -> (x + const0) + y
					if (s->move.right->binop.op == '+' &&
						s->move.right->binop.right->kind == T_Exp::T_CONST &&

						s->move.right->binop.left->kind == T_Exp::T_BINOP &&
						s->move.right->binop.left->binop.op == '+' &&
						s->move.right->binop.left->binop.right->kind == T_Exp::T_TEMP)
					{
						T_Exp* t = s->move.right->binop.left->binop.right;
						s->move.right->binop.left->binop.right = s->move.right->binop.right;
						s->move.right->binop.right = t;
					}

					// convert (x + const0) + const1 -> x + (const0 + const1)
					if (s->move.right->binop.op == '+')
					{
						if (s->move.right->binop.right->kind == T_Exp::T_CONST)
						{
							if (s->move.right->binop.left->kind == T_Exp::T_BINOP)
							{
								if (s->move.right->binop.left->binop.right->kind == T_Exp::T_CONST)
								{
									s->move.right = T_BinopExp(
										'+',
										s->move.right->binop.left->binop.left,
										T_ConstExp(s->move.right->binop.left->binop.right->const_int.int32 + s->move.right->binop.right->const_int.int32));
								}
							}
						}
					}
					else if (s->move.right->binop.op == '-')
					{
						if (s->move.right->binop.right->kind == T_Exp::T_CONST)
						{
							if (s->move.right->binop.left->binop.right->kind == T_Exp::T_CONST)
							{
								s->move.right = T_BinopExp(
									'+',
									s->move.right->binop.left->binop.left,
									T_ConstExp(s->move.right->binop.left->binop.right->const_int.int32 - s->move.right->binop.right->const_int.int32));
							}
						}
					}
					*/
				}

				// convert (x + const0) + const1 -> x + (const0 + const1)
				if (s->move.right->binop.op == '+')
				{
					if (s->move.right->binop.right->kind == T_Exp::T_CONST)
					{
						if (s->move.right->binop.left->kind == T_Exp::T_BINOP)
						{
							if (s->move.right->binop.left->binop.right->kind == T_Exp::T_CONST)
							{
								s->move.right = T_BinopExp(
									'+',
									s->move.right->binop.left->binop.left,
									T_ConstExp(s->move.right->binop.left->binop.right->const_int.int32 + s->move.right->binop.right->const_int.int32));

								changed++;
								printf("***\n");
								print(s);
								printf("\n");
							}
						}
					}
				}
			}
		}
		/*
		else if (e->binop.left->kind == T_Exp::T_MEM)
		{
		}
		else if (e->binop.left->kind == T_Exp::T_BINOP)
		{
		}
		*/
		else
		{
			unfold(s, e->binop.left);
		}

		if (e->binop.right->kind == T_Exp::T_TEMP)
		{
			T_Stm* defsite = def[e->binop.right->temp];

			T_Exp* defexp = defsite->move.right;

			if (defexp->kind == T_Exp::T_BINOP)
			{
				T_StmList* u = uses[defsite->move.left->temp];
				//if (u && u->tail == NULL)
				{
					//T_StmList* & u = uses[defsite->move.left->temp];
					uses[defsite->move.left->temp] = remove_node(uses[defsite->move.left->temp], s);

					stm_uselist = remove_temp(stm_uselist, defsite->move.left->temp);

					s->move.right->binop.right = T_BinopExp(defexp->binop.op, defexp->binop.left, defexp->binop.right);

					/*
					if (defexp->binop.left->kind == T_Exp::T_TEMP)
					{
						stm_uselist = new Temp_tempList(defexp->binop.left->temp, stm_uselist);
						uses[defexp->binop.left->temp] = new T_StmList(s, uses[defexp->binop.left->temp]);
					}

					if (defexp->binop.right->kind == T_Exp::T_TEMP)
					{
						stm_uselist = new Temp_tempList(defexp->binop.right->temp, stm_uselist);
						uses[defexp->binop.right->temp] = new T_StmList(s, uses[defexp->binop.right->temp]);
					}
					*/
						{
							Temp_tempList* stm_uselist2 = stm_uses[defsite];
							while (stm_uselist2)
							{
								uses[stm_uselist2->temp] = new T_StmList(s, uses[stm_uselist2->temp]);
								stm_uselist = new Temp_tempList(stm_uselist2->temp, stm_uselist);

								stm_uselist2 = stm_uselist2->tail;
							}
						}

					changed++;
					printf("***\n");
					print(s);
					printf("\n");
				}
			}
		}
		else
		{
			unfold(s, e->binop.right);
		}

		// (x + const0) + (y + const1) -> (x + (const0+const1)) + y
		if (e->binop.op == '+' &&

			e->binop.left->kind == T_Exp::T_BINOP &&
			e->binop.left->binop.right->kind == T_Exp::T_CONST &&

			e->binop.right->kind == T_Exp::T_BINOP &&
			e->binop.right->binop.right->kind == T_Exp::T_CONST)
		{
			e =
				T_BinopExp('+',

					T_BinopExp('+',
							e->binop.left->binop.left,
							T_ConstExp(e->binop.left->binop.right->const_int.int32 + e->binop.right->binop.right->const_int.int32)
					),

					e->binop.right->binop.left);

			changed++;
			printf("***\n");
			print(s);
			printf("\n");
		}

		/*
		if (s->move.right->binop.right->kind == T_Exp::T_TEMP)
		{
		//	src = new Temp_tempListr(&s->move.right->binop.right->temp, src);

			T_Exp* defsite = ssa_tempStack[s->move.right->binop.right->temp]->move.right;
			if (defsite->kind == T_Exp::T_BINOP)
			{
				s->move.right->binop.right = T_BinopExp(defsite->binop.op, defsite->binop.left, defsite->binop.right);
			}
		}
		*/

#endif
	}
	/*
	else if (s->move.right->kind == T_Exp::T_UNOP)
	{
		ASSERT(s->move.right->unop.exp->kind == T_Exp::T_TEMP);

		src = new Temp_tempListr(&s->move.right->unop.exp->temp, NULL);
	}
	*/
	else if (e->kind == T_Exp::T_CONST)
	{
	}
	else if (e->kind == T_Exp::T_TEMP)
	{
		T_Stm* defsite = def[e->temp];

		if (defsite)
		{
			T_Exp* defexp = defsite->move.right;

		//	if (defexp->kind == T_Exp::T_BINOP)
			{
				T_StmList* u = uses[defsite->move.left->temp];
			//	if (u && u->tail == NULL)
				{

					T_StmList* & u = uses[defsite->move.left->temp];
					u = remove_node(u, s);

					stm_uselist = remove_temp(stm_uselist, defsite->move.left->temp);

					/*
					if (defexp->binop.left->kind == T_Exp::T_TEMP)
					{
						stm_uselist = new Temp_tempList(defexp->binop.left->temp, stm_uselist);
						uses[defexp->binop.left->temp] = new T_StmList(s, uses[defexp->binop.left->temp]);
					}

					if (defexp->binop.right->kind == T_Exp::T_TEMP)
					{
						stm_uselist = new Temp_tempList(defexp->binop.right->temp, stm_uselist);
						uses[defexp->binop.right->temp] = new T_StmList(s, uses[defexp->binop.right->temp]);
					}
					*/
					{
						Temp_tempList* stm_uselist2 = stm_uses[defsite];
						while (stm_uselist2)
						{
							uses[stm_uselist2->head] = new T_StmList(s, uses[stm_uselist2->head]);
							stm_uselist = new Temp_tempList(stm_uselist2->head, stm_uselist);

							stm_uselist2 = stm_uselist2->tail;
						}
					}

					e = defexp->Clone();//T_BinopExp(defexp->binop.op, defexp->binop.left, defexp->binop.right);

					changed++;
					printf("***\n");
					print(s);
					printf("\n");
				}
			}
		}
	}
	else if (e->kind == T_Exp::T_MEM)
	{
		changed += unfold(s, e->mem.mem);
#if 0
		T_Stm* defsite = def[e->mem.mem->temp];

		if (defsite)
		{
			T_Exp* defexp = defsite->move.right;

			if (defexp->kind == T_Exp::T_MEM)
			{
				uses[defsite->move.left->temp] = remove_node(uses[defsite->move.left->temp], s);
				stm_uselist = remove_temp(stm_uselist, defsite->move.left->temp);

				Temp_tempList* stm_uselist2 = stm_uses[defsite];
				while (stm_uselist2)
				{
					uses[stm_uselist2->temp] = new T_StmList(s, uses[stm_uselist2->temp]);
					stm_uselist = new Temp_tempList(stm_uselist2->temp, stm_uselist);

					stm_uselist2 = stm_uselist2->tail;
				}

				s->move.right->mem.mem = defexp;//T_BinopExp(defexp->binop.op, defexp->binop.left, defexp->binop.right);
			}
			else if (defexp->kind == T_Exp::T_BINOP)
			{
				T_StmList* & u = uses[defsite->move.left->temp];
				if (u && u->tail == NULL)
				{
					T_StmList* & u = uses[defsite->move.left->temp];
					u = remove_node(u, s);

					stm_uselist = remove_temp(stm_uselist, defsite->move.left->temp);

					/*
					if (defexp->binop.left->kind == T_Exp::T_TEMP)
						stm_uselist = new Temp_tempList(defexp->binop.left->temp, stm_uselist);

					if (defexp->binop.right->kind == T_Exp::T_TEMP)
						stm_uselist = new Temp_tempList(defexp->binop.right->temp, stm_uselist);
						*/
					{
						Temp_tempList* stm_uselist2 = stm_uses[defsite];
						while (stm_uselist2)
						{
							uses[stm_uselist2->temp] = new T_StmList(s, uses[stm_uselist2->temp]);
							stm_uselist = new Temp_tempList(stm_uselist2->temp, stm_uselist);

							stm_uselist2 = stm_uselist2->tail;
						}
					}

					e->mem.mem = T_BinopExp(defexp->binop.op, defexp->binop.left, defexp->binop.right);

					changed++;
				}
			}
		}
#endif
	}

	return changed;
}

int unfolding(T_StmList* n)
{
//	map<Temp_temp**, T_Stm*> ssa_tempStack;
	//map<Temp_temp**, int> ssa_count;

	int changed = 0;

	T_StmList* slist = n;
	while (slist)
	{
		T_Stm* s = slist->head;

		Temp_tempList* & stm_uselist = stm_uses[s];
		
		if (s->kind == T_Stm::T_MOVE)
		{
			/*
			Temp_tempListr* dst = NULL;
			if (s->move.left->kind == T_Exp::T_TEMP)
			{
				dst = new Temp_tempListr(&s->move.left->temp, NULL);
			}

			Temp_tempListr* src = NULL;
			*/
			if (s->move.right->kind == T_Exp::T_BINOP)
			{
				// constant propagation

				/*
				if (s->move.right->binop.left->kind == T_Exp::T_TEMP)
				{
					T_Stm* defsite = ssa_tempStack[s->move.right->binop.left->temp];

					if (defsite->move.right->kind == T_Exp::T_CONST)	// constant propagation
					{
						s->move.right->binop.left = T_ConstExp(defsite->move.right->const_int.int32);
					}
					else if (defsite->move.right->kind == T_Exp::T_TEMP)	// copy propagation
					{
						s->move.right->binop.left = T_Temp(defsite->move.right->temp);
					}
				}

				if (s->move.right->binop.right->kind == T_Exp::T_TEMP)
				{
					T_Stm* defsite = ssa_tempStack[s->move.right->binop.right->temp];

					if (defsite->move.right->kind == T_Exp::T_CONST)	// constant propagation
					{
						s->move.right->binop.right = T_ConstExp(defsite->move.right->const_int.int32);
					}
					else if (defsite->move.right->kind == T_Exp::T_TEMP)	// copy propagation
					{
						s->move.right->binop.right = T_Temp(defsite->move.right->temp);
					}
				}

				// constant folding
				// convert (const0 op const0) -> const1
				if (s->move.right->binop.left->kind == T_Exp::T_CONST &&
					s->move.right->binop.right->kind == T_Exp::T_CONST)
				{
					if (s->move.right->binop.op == '+')
					{
						s->move.right = T_ConstExp(s->move.right->binop.left->const_int.int32 + s->move.right->binop.right->const_int.int32);
					}
					else if (s->move.right->binop.op == '-')
					{
						s->move.right = T_ConstExp(s->move.right->binop.left->const_int.int32 - s->move.right->binop.right->const_int.int32);
					}
					else if (s->move.right->binop.op == '*')
					{
						s->move.right = T_ConstExp(s->move.right->binop.left->const_int.int32 * s->move.right->binop.right->const_int.int32);
					}
				}
				else
				*/
				// convert (const0 (+)/(*) x) -> (x (+)/(*) const0)
				if ((s->move.right->binop.op == '+' || s->move.right->binop.op == '*') &&
					s->move.right->binop.left->kind == T_Exp::T_CONST/* &&
					s->move.right->binop.right->kind == T_Exp::T_TEMP*/)
				{
					T_Exp* t = s->move.right->binop.left;
					s->move.right->binop.left = s->move.right->binop.right;
					s->move.right->binop.right = t;

					changed++;
					printf("***\n");
					print(s);
					printf("\n");
				}
			}

			if (s->move.left->kind == T_Exp::T_MEM)
			{
				changed += unfold(s, s->move.left->mem.mem);
			}

			changed += unfold(s, s->move.right);


			/*
			if (true)	// not a ø-function
			{
				Temp_tempListr* xlist = src;
				while (xlist)
				{
					Temp_temp** x = *xlist->temp;

					printf("use: %p\n", x);

					//ASSERT(ssa_tempStack[x].size());
				//	Temp_temp** xi = ssa_tempStack[x];//.top();
				

				//	*xlist->temp = xi;

					xlist = xlist->tail;
				}
			}
			*/

#if 0
			Temp_tempListr* xlist = dst;
			while (xlist)
			{
				Temp_temp** x = *xlist->temp;

		//		printf("def: %p\n", x);

		//		int i = ++ssa_count[x];

				/*
				Temp_temp** xi = new Temp_temp*;
				*xi = new Temp_temp;

				char* name_i = new char[256];
				sprintf(name_i, "%s_%d", (*x)->name, i);
				(*xi)->name = name_i;
				*/

				ssa_tempStack[x] = s;//->move.right;//.push(xi);

			//	*xlist->temp = xi;

				xlist = xlist->tail;
			}
#endif
		}
		else if (s->kind == T_Stm::T_EXP)
		{
			T_Exp* e = s->exp;

			if (e->kind == T_Exp::T_CALL)
			{
				ArgList* args = e->call.args;

				while (args)
				{
					if (args->head->kind == T_Exp::T_TEMP)
					{
						changed++;

						T_Stm* defsite = def[args->head->temp];

						uses[args->head->temp] = remove_node(uses[args->head->temp], s);
						stm_uselist = remove_temp(stm_uselist, args->head->temp);

						Temp_tempList* stm_uselist2 = stm_uses[defsite];
						while (stm_uselist2)
						{
							uses[stm_uselist2->head] = new T_StmList(s, uses[stm_uselist2->head]);
							stm_uselist = new Temp_tempList(stm_uselist2->head, stm_uselist);

							stm_uselist2 = stm_uselist2->tail;
						}

						args->head = defsite->move.right;
					}

					args = args->tail;
				}
			}
			else
				ASSERT(0);
		}

		slist = slist->tail;
	}

	return changed;
}

int change(T_Declarator* frame, T_StmList* n)
{
	Temp_tempList* tlist = NULL;

	int changed = 0;

	{
		T_StmList* slist = n;
		while (slist)
		{
			T_Stm* s = slist->head;
			
			if (s->kind == T_Stm::T_MOVE)
			{
				if (s->move.right->kind == T_Exp::T_ADDRESSOF)
				{
					ASSERT(s->move.right->addressof->kind == T_Exp::T_TEMP);
					tlist = new Temp_tempList(s->move.right->addressof->temp, tlist);
					changed++;
				}
			}
			else if (s->kind == T_Stm::T_EXP)
			{
				T_Exp* e = s->exp;

				if (e->kind == T_Exp::T_CALL)
				{
					ArgList* args = e->call.args;
					while (args)
					{
						args = args->tail;
					}
				}
			}

			slist = slist->tail;
		}
	}

	while (tlist)
	{
		Temp_temp** temp = tlist->head;

		T_Stm* defsite = def[temp];

		int _sizeof = (*temp)->m_size;

		frame->m_stackSize += _sizeof;
		int offset = -frame->m_stackSize;

		defsite->move.left = T_Mem(T_BinopExp('+', T_Temp(&a5), T_ConstExp(offset)), _sizeof);
		quadruples(defsite);
		//slist = linear(do_stm(s), slist->tail);

	//	def[temp] = NULL;//remove_node(def[temp], defsite);
		//stm_uses[defsite] = remove_temp(stm_uses[defsite], temp);

		T_StmList* tempuses = uses[temp];
		while (tempuses)
		{
			T_Stm* s = tempuses->head;

			if (s->kind == T_Stm::T_MOVE)
			{
				if (s->move.right->kind == T_Exp::T_ADDRESSOF)
				{
					s->move.right = T_BinopExp('+', T_Temp(&a5), T_ConstExp(offset));
				//	uses[temp] = remove_node(uses[temp], s);
				//	stm_uses[s] = remove_temp(stm_uses[s], temp);
				}
				else if (s->move.right->kind == T_Exp::T_TEMP)
				{
					s->move.right = T_Mem(T_BinopExp('+', T_Temp(&a5), T_ConstExp(offset)), _sizeof);
				//	uses[temp] = remove_node(uses[temp], s);
				//	stm_uses[s] = remove_temp(stm_uses[s], temp);
				}
				else if (s->move.right->kind == T_Exp::T_BINOP)
				{
					ASSERT(0);
				}
			}
			else if (s->kind == T_Stm::T_EXP)
			{
				if (s->exp->kind == T_Exp::T_CALL)
				{
					ArgList* args = s->exp->call.args;
					while (args)
					{
						if (args->head->kind == T_Exp::T_TEMP)
						{
							if (args->head->temp == temp)
							{
								args->head = T_Mem(T_BinopExp('+', T_Temp(&a5), T_ConstExp(offset)), _sizeof);
							}
						}

						args = args->tail;
					}
				}
			}

			quadruples(s);

			tempuses = tempuses->tail;
		}

		tlist = tlist->tail;
	}

	return changed;
}

template<class l_t, class n_t> int find_index(l_t* _l, n_t* _n)
{
	int index = 0;

	while (_l)
	{
		if (_l->head == _n)
			return index;

		++index;

		_l = _l->tail;
	}

	return -1;
}

template<class l_t> l_t* find_index(l_t* _l, int index)
{
	while (index--)
	{
		_l = _l->tail;
	}

	return _l;
}

Temp_tempList* ssa_variables = NULL;

void ssa_rename(C_stmListList* n, map<Temp_temp**, stack<Temp_temp**> >&  ssa_tempStack, map<Temp_temp**, int>& ssa_count)
{
//	map<Temp_temp**, stack<Temp_temp**> > ssa_tempStack;
//	map<Temp_temp**, int> ssa_count;
//	ssa_tempStack[&a5].push(&a5);//.push();

	T_StmList* slist = n->head;
	while (slist)
	{
		T_Stm* s = slist->head;
		
		if (s->kind == T_Stm::T_CJUMP)
		{
			expRefList* src = NULL;

			if (s->cjump.left->kind == T_Exp::T_TEMP)
			{
				src = new expRefList(&s->cjump.left, src);
			}

			if (s->cjump.right->kind == T_Exp::T_TEMP)
			{
				src = new expRefList(&s->cjump.right, src);
			}

			{
				expRefList* xlist = src;
				while (xlist)
				{
					Temp_temp** x = (*xlist->head)->temp;

					printf("use: %p\n", x);

					//ASSERT(ssa_tempStack[x].size());
					Temp_temp** xi = ssa_tempStack[x].top();

					Temp_tempList* & stm_uselist = stm_uses[s];
					stm_uselist = new Temp_tempList(xi, stm_uselist);

					tempuses_exprefs[xi] = new expRefList(xlist->head, tempuses_exprefs[xi]);

					T_StmList* & u = uses[xi];
					u = new T_StmList(s, u);

					(*xlist->head)->temp = xi;

					xlist = xlist->tail;
				}
			}
		}
		else if (s->kind == T_Stm::T_MOVE)
		{
			Temp_tempListr* dst = NULL;
			expRefList* src = NULL;

			if (s->move.left->kind == T_Exp::T_TEMP)
			{
				dst = new Temp_tempListr(&s->move.left->temp, NULL);
			}
			else
			{
				ASSERT(s->move.left->kind == T_Exp::T_MEM);
				ASSERT(s->move.left->mem.mem->kind == T_Exp::T_TEMP);
				src = new expRefList(&s->move.left->mem.mem, NULL);
			}

			if (s->move.right->kind != T_Exp::T_PHI)
			{
				if (s->move.right->kind == T_Exp::T_TEMP)
				{
					src = new expRefList(&s->move.right, src);
				}
				else if (s->move.right->kind == T_Exp::T_BINOP)
				{
					if (s->move.right->binop.left->kind == T_Exp::T_TEMP)
					{
						src = new expRefList(&s->move.right->binop.left, src);
					}
					else if (s->move.right->binop.left->kind == T_Exp::T_MEM)
					{
						src = new expRefList(&s->move.right->binop.left->mem.mem, src);
					}

					if (s->move.right->binop.right->kind == T_Exp::T_TEMP)
					{
						src = new expRefList(&s->move.right->binop.right, src);
					}
					else if (s->move.right->binop.right->kind == T_Exp::T_MEM)
					{
						src = new expRefList(&s->move.right->binop.right->mem.mem, src);
					}
				}
				else if (s->move.right->kind == T_Exp::T_UNOP)
				{
					ASSERT(s->move.right->unop.exp->kind == T_Exp::T_TEMP);

					src = new expRefList(&s->move.right->unop.exp, src);
				}
				else if (s->move.right->kind == T_Exp::T_CONST)
				{
				}
				else if (s->move.right->kind == T_Exp::T_MEM)
				{
					if (s->move.right->mem.mem->kind == T_Exp::T_TEMP)
					{
						src = new expRefList(&s->move.right->mem.mem, src);
					}
					else if (s->move.right->mem.mem->kind == T_Exp::T_NAME)
					{
						//src = new Temp_tempListr(&s->move.right->mem.mem->temp, NULL);
					}
				}
				else if (s->move.right->kind == T_Exp::T_ADDRESSOF)
				{
					if (s->move.right->addressof->kind == T_Exp::T_TEMP)
					{
						src = new expRefList(&s->move.right->addressof, src);
					}
					else
						ASSERT(0);
					/*
					else if (s->move.right->mem.mem->kind == T_Exp::T_NAME)
					{
						//src = new Temp_tempListr(&s->move.right->mem.mem->temp, NULL);
					}
					*/
				}
				else
					ASSERT(0);
			}

			//if (true)	// not a ø-function
			{
				expRefList* xlist = src;
				while (xlist)
				{
					Temp_temp** x = (*xlist->head)->temp;

					printf("use: %p\n", x);

					//ASSERT(ssa_tempStack[x].size());
					Temp_temp** xi = ssa_tempStack[x].top();

					Temp_tempList* & stm_uselist = stm_uses[s];
					stm_uselist = new Temp_tempList(xi, stm_uselist);

					tempuses_exprefs[xi] = new expRefList(xlist->head, tempuses_exprefs[xi]);

					T_StmList* & u = uses[xi];
					u = new T_StmList(s, u);

					(*xlist->head)->temp = xi;

					xlist = xlist->tail;
				}
			}

			Temp_tempListr* xlist = dst;
			while (xlist)
			{
				Temp_temp** x = *xlist->temp;

				printf("def: %p\n", x);

				int i = ++ssa_count[x];

				Temp_temp** xi = new Temp_temp*;
				*xi = new Temp_temp;

				ssa_variables = new Temp_tempList(xi, ssa_variables);

				char* name_i = new char[256];
				sprintf_s(name_i, 256, "%s_%d", (*x)->name, i);
				(*xi)->name = name_i;

				ssa_tempStack[x].push(xi);

				def[xi] = s;

				//x->m_alias = xi;

				*xlist->temp = xi;

				xlist = xlist->tail;
			}
		}
		else if (s->kind == T_Stm::T_EXP)
		{
			T_Exp* e = s->exp;

			if (e->kind == T_Exp::T_CALL)
			{
				ArgList* args = e->call.args;
				while (args)
				{
					if (args->head->kind == T_Exp::T_TEMP)
					{
						Temp_temp** x = args->head->temp;
						Temp_temp** xi = ssa_tempStack[x].top();

						Temp_tempList* & stm_uselist = stm_uses[s];
						stm_uselist = new Temp_tempList(xi, stm_uselist);

						tempuses_exprefs[xi] = new expRefList(&args->head, tempuses_exprefs[xi]);

						T_StmList* & u = uses[xi];
						u = new T_StmList(s, u);

						args->head->temp = xi;
					}
					else if (args->head->kind == T_Exp::T_NAME)
					{
					}
					else
						ASSERT(0);

					args = args->tail;
				}
			}
			else
				ASSERT(0);
		}

		slist = slist->tail;
	}

	C_stmListListList* succlist = n->succ;
	while (succlist)
	{
		C_stmListList* succ = succlist->head;

		int j = find_index(succ->pred, n);

		// for each ø-function in succ
		T_StmList* stmList = succ->head;
		while (stmList)
		{
			T_Stm* s = stmList->head;

			if (s->kind == T_Stm::T_MOVE && s->move.right->kind == T_Exp::T_PHI)
			{
				Temp_tempList* a = find_index(s->move.right->phi.temps, j);

				Temp_temp** i = ssa_tempStack[a->head].top();

				a->head = i;

			//	find_index(, j)->head = ;
			}

			stmList = stmList->tail;
		}

		succlist = succlist->tail;
	}

	C_stmListListList* c = n->children;
	while (c)
	{
		ssa_rename(c->head, ssa_tempStack, ssa_count);
		c = c->tail;
	}
}

template<class l_t, class n_t> l_t* find(l_t* _l, n_t* _n)
{
	while (_l)
	{
		if (_l->head == _n)
			break;

		_l = _l->tail;
	}

	return _l;
}

void computeDF(C_stmListList* n, map<C_stmListList*,C_stmListListList*> & DF, map<C_stmListList*, C_stmListList*>& idom, map<C_stmListList*, C_stmListListList*>& dom)
{
	C_stmListListList* S = NULL;

	// compute DF_local[n]
	C_stmListListList* y = n->succ;
	while (y)
	{
		if (idom[y->head] != n)
		{
			S = new C_stmListListList(y->head, S);
		}
		y = y->tail;
	}

	C_stmListListList* c = n->children;
	while (c)
	{
		computeDF(c->head, DF, idom, dom);

		C_stmListListList* w = DF[c->head];
		while (w)
		{
			if (!find(dom[w->head], n))	// if n does not dominate w
			{
				S = new C_stmListListList(w->head, S);
			}

			w = w->tail;
		}

		c = c->tail;
	}

	DF[n] = S;
}

void edge_splitting(C_stmListListList* nodes)
{
	C_stmListListList* n = nodes;
	while (n)
	{
		C_stmListListList* succs = n->head->succ;

		if (succs && succs->tail)	// multiple successors
		{
			while (succs)
			{
				C_stmListList* succ = succs->head;

				if (succ->pred->tail)
				{
					ASSERT(0);
				}

				succs = succs->tail;
			}
		}

		n = n->tail;
	}
}

void place_phi_functions(C_stmListListList* nodes, map<C_stmListList*,C_stmListListList*> & DF)
{
	//map<C_stmListList*, Temp_tempList*> ast::A_orig

	Temp_tempList* variables = NULL;
	map<Temp_temp**, C_stmListListList*> defsites;

	C_stmListListList* n = nodes;
	while (n)
	{
		T_StmList* slist = n->head->head;
		while (slist)
		{
			T_Stm* s = slist->head;
			if (s->kind == T_Stm::T_MOVE)
			{
				if (s->move.left->kind == T_Exp::T_TEMP)
				{
					if (!find(variables, s->move.left->temp))
						variables = new Temp_tempList(s->move.left->temp, variables);

					defsites[s->move.left->temp] = new C_stmListListList(n->head, defsites[s->move.left->temp]);
				}
			}

			slist = slist->tail;
		}

		n = n->tail;
	}

	// The set of nodes that must have ø-functions for a variable
	map<Temp_temp**, C_stmListListList*> A;

	Temp_tempList* alist = variables;
	while (alist)
	{
		Temp_temp** a = alist->head;

		C_stmListListList* W = defsites[a];		

		while (W)
		{
			C_stmListList* n = W->head;
			W = W->tail;

			C_stmListListList* ylist = DF[n];
			while (ylist)
			{
				C_stmListList* y = ylist->head;

				if (!find(A[a], y))
				{
					// insert a ø-function at top of block
					ASSERT(y->head->head->kind == T_Stm::T_LABEL);

					Temp_tempList* temps = NULL;
					C_stmListListList* preds = y->pred;
					while (preds)
					{
						temps = new Temp_tempList(a, temps);
						preds = preds->tail;
					}

					y->head->tail = new T_StmList(T_MoveStm(T_Temp(a), new T_Phi(y->pred, Reverse(temps))), y->head->tail);
					A[a] = new C_stmListListList(y, A[a]);
				}

			//	W = new C_stmListListList(y, W);

				ylist = ylist->tail;
			}
		}

		alist = alist->tail;
	}
}

void from_ssa(C_stmListListList* nodes)
{
	C_stmListListList* n = nodes;

	while (n)
	{
		T_StmList* slistprev = NULL;
		T_StmList* slist = n->head->head;

		while (slist)
		{
			T_Stm* s = slist->head;

			if (s->kind == T_Stm::T_MOVE && s->move.right->kind == T_Exp::T_PHI)
			{
				Temp_tempList* temps = s->move.right->phi.temps;

				int index = 0;
				while (temps)
				{
					C_stmListListList* prev = find_index(n->head->pred, index);

					T_StmList* prevstms = prev->head->head;
					while (prevstms->tail->tail)
					{
						prevstms = prevstms->tail;
					}

					ASSERT(prevstms->tail->head->kind == T_Stm::T_JUMP || prevstms->tail->head->kind == T_Stm::T_CJUMP);

					prevstms->tail = new T_StmList(T_MoveStm(T_Temp(s->move.left->temp), T_Temp(temps->head)), prevstms->tail);

					++index;
					temps = temps->tail;
				}

				slistprev->tail = slist->tail;
			}

			slistprev = slist;
			slist = slist->tail;
		}

		n = n->tail;
	}
}

template<class List, class Node> void InsertBefore(List* pList, Node* newChild, Node* pBefore)
{
	Node* pAfter;

	if (pBefore)
		pAfter = pBefore->prev;
	else
		pAfter = pList->tail;

	newChild->next = pBefore;
	newChild->prev = pAfter;

	if (pAfter == NULL)
		pList->head = newChild;
	else
		pAfter->next = newChild;

	if (pBefore == NULL)
		pList->tail = newChild;
	else
		pBefore->prev = newChild;
}

void gen(const char* fileoutpath, int m_exeType, const vector<T_Declarator*>& tglobals, CGlobal* pGlobal, Scope* pGlobalScope)
{
	if (false)//if (false && errors == 0)
	{
//			CCompileFile cf;

		printf("Generating Code...\n");

		FILE* fileout;
		errno_t err = fopen_s(&fileout, fileoutpath, "w+b");
		if (fileout)
		{
			CCodeGenerator* pCodeGen;

			if (m_exeType == 1)
			{
				pCodeGen = new CCodeGen68k;
				((CCodeGen68k*)pCodeGen)->fileout = fileout;
			}
			/*
			else if (m_exeType == 2)
				pCodeGen = new CCodeGenx86;
			else if (m_exeType == 3)
				pCodeGen = new CCodeGenPPC;
				*/
			else
				ASSERT(0);

#if 0
			CArray<CDeclarator*, CDeclarator*> globals;

			{
				for (int i = 0; i < pGlobal->m_globals.GetSize(); i++)
				{
					__live_object_ptr<CDeclarator> pDeclarator = pGlobal->m_globals[i];

					if (pDeclarator->m_pType->GetType()->m_type == type_function &&
						pDeclarator->m_pType->GetType()->GetFunction()->m_funcspec == 5/*cpp::KW_INLINE*/)
					{
						continue;
					}

					{
						printf("%s\n", pDeclarator->m_name->c_str());
						/*pObjectFile->*/globals.Add(pDeclarator);
					}
				}

#if 0
				// Types, determine referenced declarations and Translation into intermediate code
				{
					for (int i = 0; i < pObjectFile->globals.size(); i++)
					{
						T_Declarator* pDeclarator = pObjectFile->globals[i];

						if (pDeclarator->m_pDeclarator->m_pType->GetType()->m_type == cpp::type_function)
						{
							if (pDeclarator->m_pDeclarator->m_pBody)
							{
#if 0
							//	T_Frame* frame = new T_Frame;
								pDeclarator->epilogue_label = new Temp_label;

								T_Stm* pStmt = NULL;
								for (int i = 0; i < pDeclarator->m_pDeclarator->m_pBody->m_statements.size(); i++)
								{
									T_Stm* p = cf.TransStatement(pDeclarator, pDeclarator->m_pDeclarator->m_pBody->m_statements[i], pDeclarator->m_pDeclarator->m_pBody->m_pScope, pGlobal, NULL/*pInnermostSwitch*/, NULL/*break_target*/);
									if (p)
									{
										if (pStmt)
											pStmt = T_Seq(pStmt, p);
										else
											pStmt = p;
									}
								}

								if (pStmt)
									pStmt = T_Seq(pStmt, T_Label(pDeclarator->epilogue_label));
								else
									pStmt = T_Label(pDeclarator->epilogue_label);

						//		pStmt = TransStatement(pDeclarator->m_pBody->m_statements[1]);

							//	statementList = Canonicalize(IR);
								if (pStmt)
									pDeclarator->m_statementList = linearize(pStmt);
								else
									pDeclarator->m_statementList = NULL;

								C_block = block = C_basicBlocks(pDeclarator->m_statementList);
#endif
							}
						}
					}
				}
#endif

				for (i = 0; i < pGlobal->m_strings.size(); i++)
				{
					ASSERT(pGlobal->m_strings[i]->m_tempLabel != NULL);
					/*pObjectFile->*/globals.Add(pGlobal->m_strings[i]);
				}

				for (i = 0; i < pGlobal->m_references.size(); i++)
				{
					__live_object_ptr<CDeclarator> pDeclarator = pGlobal->m_references[i];

					if (pDeclarator->m_pType->GetType()->m_type == type_function && pDeclarator->m_pType->GetType()->GetFunction()->m_libcall.m_offset != 0)
						continue;

					if (	!pDeclarator->m_defined &&
							pDeclarator->m_referenced
						)//m_referenced == 1)
					{
						printf("extern: %s\n", pDeclarator->m_name->c_str());

						/*pObjectFile->*/globals.Add(pDeclarator);//TDeclarator);
					}
				}

				{
					for (int i = 0; i < /*pObjectFile->*/globals.GetSize(); i++)
					{
						__live_object_ptr<CDeclarator> pDeclarator = /*pObjectFile->*/globals[i];

						if (false && pDeclarator->m_pType->GetType()->m_type == type_function)
						{
							char name[256];
							sprintf(name, "_%s@%d", pDeclarator->/*m_pDeclarator->*/m_name->c_str(), pDeclarator->m_pType->GetType()->GetFunction()->m_stackSize);
							pDeclarator->m_mangledName = new StringA(name);
						}
						else if (pDeclarator->m_name->Length())
						{
							char name[256];
							sprintf(name, "_%s", pDeclarator->m_name->c_str());
							pDeclarator->m_mangledName = new StringA(name);
						}

						if (pDeclarator->m_tempLabel == NULL)
							pDeclarator->m_tempLabel = new Temp_label;

						pDeclarator->m_tempLabel->m_defined = pDeclarator->m_defined;

#if 0
						if (pDeclarator->m_mangledName.length())
						{

							FSymbol* pSymbol;
							pDeclarator->m_tempLabel->m_symbolIndex = pObjectFile->AddSymbol(pDeclarator->m_mangledName.c_str(), &pSymbol);
							pSymbol->m_tempLabel = pDeclarator->m_tempLabel;
						}
#endif
					}
				}
			}
#endif

			CFunctionCode* pCode = new CFunctionCode;

			pCode->emit(AS_Source("c:\\test_compile.cpp"));

			{
				for (uint i = 0; i < /*pObjectFile->*/tglobals.GetSize(); ++i)
				{
					T_Declarator* pDeclarator = /*pObjectFile->*/tglobals[i];

					if (pDeclarator->m_tempLabel->m_defined)
					{
						if (pDeclarator->type == T_Declarator::function)
						{
					//	pDeclarator->m_statementList = linearize(pDeclarator->m_statementList);

							C_block block = C_basicBlocks(pDeclarator->m_statementList, pDeclarator->epilogue_label);

							if (true)	// (debug) (don't rearrange order of basic blocks)
							{
								block.stmLists = new C_stmListListList(new C_stmListList(new T_StmList(T_Label(pDeclarator->epilogue_label), NULL)), block.stmLists);
								block.stmLists->head->head->head->m_block = block.stmLists->head;
								block.labels[pDeclarator->epilogue_label] = block.stmLists->head;

								block.stmLists = Reverse(block.stmLists);

								{
									C_stmListListList* stmlists = block.stmLists;
									while (stmlists)
									{
										T_StmList* stms = stmlists->head->head;

										while (stms->tail)
										{
											ASSERT(stms->head->m_block == stmlists->head);

											stms = stms->tail;
										}

										ASSERT(stms->head->m_block == stmlists->head);

										if (stms->head->kind == T_Stm::T_JUMP)
										{
											Temp_labelList* labels = stms->head->jump.labels;

											while (labels)
											{
												C_stmListList* b = block.labels[labels->head];

												b->pred = new C_stmListListList(stmlists->head, b->pred);
												stmlists->head->succ = new C_stmListListList(b, stmlists->head->succ);

												labels = labels->tail;
											}
										}
										else if (stms->head->kind == T_Stm::T_CJUMP)
										{
											C_stmListList* b;
											
											b = block.labels[stms->head->cjump.t];
											b->pred = new C_stmListListList(stmlists->head, b->pred);
											stmlists->head->succ = new C_stmListListList(b, stmlists->head->succ);

											b = block.labels[stms->head->cjump.f];
											b->pred = new C_stmListListList(stmlists->head, b->pred);
											stmlists->head->succ = new C_stmListListList(b, stmlists->head->succ);
										}
										else
											;//ASSERT(0);

										stmlists = stmlists->tail;
									}
								}
							}
							else	// release
							{
								block.stmLists = Reverse(block.stmLists);

								T_StmList* stmlist = C_traceSchedule(block);
								stmlist = new T_StmList(T_Label(pDeclarator->epilogue_label), stmlist);

								pDeclarator->m_statementList = Reverse(stmlist);
							}

							{
								printf("*********************************\n");

								T_StmList* stm = pDeclarator->m_statementList;

								while (stm)
								{
									printf("%d\t", stm->head->m_line_pos);

									switch (stm->head->kind)
									{
									case T_Stm::T_LABEL:
										printf("label: %x", stm->head->label);
										break;

									case T_Stm::T_JUMP:
										printf("\tjump %x", stm->head->jump.labels->head);
										break;

									case T_Stm::T_CJUMP:
										printf("\tcjump t:%x f:%x", stm->head->cjump.t, stm->head->cjump.f);
										break;

									case T_Stm::T_LBRAC:
										printf("\tlbrac");
										break;

									case T_Stm::T_RBRAC:
										printf("\trbrac");
										break;

									case T_Stm::T_LSYM:
										printf("\tlsym");
										break;

									default:
										printf("\tstm");
									}

									printf("\n");

									stm = stm->tail;
								}

								printf("\n");
							//	printf("label: %x", pDeclarator->epilogue_label);

								printf("*********************************\n");
							}

							// dominance tree
							{
								map<C_stmListList*, C_stmListListList*> dom;

								C_stmListListList* blocks = block.stmLists;
								C_stmListList* s0 = blocks->head;

								// initialize

								dom[s0] = new C_stmListListList(s0, dom[s0]);

								blocks = blocks->tail;	// for all except s0
								while (blocks)
								{
									C_stmListListList* blocks2 = block.stmLists;
									while (blocks2)
									{
										dom[blocks->head] = new C_stmListListList(blocks2->head, dom[blocks->head]);

										blocks2 = blocks2->tail;
									}

									blocks = blocks->tail;
								}

								{
									C_stmListListList* n = block.stmLists;
									while (n)
									{
										printf("%x - ", n->head->head->head->label);

										C_stmListListList* Dn = dom[n->head];

										while (Dn)
										{
											printf("%x", Dn->head->head->head->label);

											Dn = Dn->tail;
											if (Dn) printf(", ");
										}

										printf(" *** ");

										C_stmListListList* predlist = n->head->pred;

										while (predlist)
										{
											printf("%x", predlist->head->head->head->label);

											predlist = predlist->tail;
											if (predlist) printf(", ");
										}

										printf("\n");

										n = n->tail;
									}
								}

								{
									printf("***** D\n");

									C_stmListListList* n = block.stmLists;
									while (n)
									{
										printf("%x - ", n->head->head->head->label);

										C_stmListListList* Dn = dom[n->head];

										while (Dn)
										{
											printf("%x", Dn->head->head->head->label);

											Dn = Dn->tail;
											if (Dn) printf(", ");
										}

										printf("\n");

										n = n->tail;
									}
								}

								int changed;

								do
								{
									changed = 0;

									C_stmListListList* n = block.stmLists;
									n = n->tail;	// for all except s0
									while (n)
									{
										C_stmListListList* & Dn = dom[n->head];

										C_stmListListList* predlist = n->head->pred;

										while (predlist)
										{
											C_stmListList* p = predlist->head;

											C_stmListListList* Dp = dom[p];

											// AND/Intersect Dn and Dp (remove from Dn those that are not found in Dp
											C_stmListListList* l = Dn;
											C_stmListListList* lpred = NULL;
											while (l)
											{
												if (l->head != n->head)
												{
													C_stmListListList* l2 = Dp;
													while (l2)
													{
														if (l2->head == l->head)
															break;

														l2 = l2->tail;
													}

													if (l2 == NULL)
													{
														if (lpred)
															lpred->tail = l->tail;
														else
															Dn = l->tail;

														changed++;
													}
												}

												lpred = l;
												l = l->tail;
											}

											//D[pred], pred->head)


											predlist = predlist->tail;
										}
										
										n = n->tail;
									}

								{
									printf("***** D\n");

									C_stmListListList* n = block.stmLists;
									while (n)
									{
										printf("%x - ", n->head->head->head->label);

										C_stmListListList* Dn = dom[n->head];

										while (Dn)
										{
											printf("%x", Dn->head->head->head->label);

											Dn = Dn->tail;
											if (Dn) printf(", ");
										}

										printf("\n");

										n = n->tail;
									}
								}

								}
								while (changed);

								{
									// Find immediate dominator

									// sdom
									map<C_stmListList*, C_stmListListList*> sdom;
									{
										C_stmListListList* n = block.stmLists;
										while (n)
										{
											C_stmListListList* Dn = dom[n->head];

											while (Dn)
											{
												if (Dn->head != n->head)
												{
													sdom[n->head] = new C_stmListListList(Dn->head, sdom[n->head]);
												}

												Dn = Dn->tail;
											}

											n = n->tail;
										}
									}

									// Find immediate dominator
									map<C_stmListList*, C_stmListList*> idom;

									{
										printf("***** D\n");

										C_stmListListList* n = block.stmLists;
										while (n)
										{
											C_stmListListList* Dn = sdom[n->head];

											// find idom for n

											C_stmListListList* Dn0 = Dn;

											while (Dn0)
											{
												C_stmListListList* Dp = sdom[Dn0->head];

												while (Dp)
												{
													if (Dp->head != n->head)
													{
														sdom[n->head] = remove_node(sdom[n->head], Dp->head);
													}

													Dp = Dp->tail;
												}

												Dn0 = Dn0->tail;
											}

											if (sdom[n->head])
											{
												ASSERT(sdom[n->head]->tail == NULL);
												idom[n->head] = sdom[n->head]->head;
											}

											printf("\n");

											n = n->tail;
										}
									}

									{
										printf("***** D\n");

										C_stmListListList* n = block.stmLists;
										while (n)
										{
											printf("%x - ", n->head->head->head->label);

											C_stmListList* Dn = idom[n->head];
											if (Dn)
											{
												Dn->children = new C_stmListListList(n->head, Dn->children);

												printf("%x", Dn->head->head->label);
											}
											printf("\n");

											n = n->tail;
										}
									}

									map<C_stmListList*,C_stmListListList*> DF;
									computeDF(block.stmLists->head, DF, idom, dom);

									/*
									{
										C_stmListList* n = block.stmLists;
										while (n)
										{
										}
									}
									*/

									edge_splitting(block.stmLists);

									place_phi_functions(block.stmLists, DF);

									def.clear();
									uses.clear();
									stm_uses.clear();

									map<Temp_temp**, stack<Temp_temp**> > ssa_tempStack;
									map<Temp_temp**, int> ssa_count;
									ssa_tempStack[&a5].push(&a5);//.push();

									ssa_rename(block.stmLists->head, ssa_tempStack, ssa_count);

									printf("***ssa_rename***************\n");
									{
										C_stmListListList* b = block.stmLists;
										while (b)
										{
											print(b->head->head);

											b = b->tail;
										}
									}
								}

								C_stmListListList* We = NULL;

								// conditional constant propagation
								{
									T_Exp* undefined = new T_Exp;
									T_Exp* overdefined = new T_Exp;

									map<Temp_temp**, T_Exp*> V;

									map<C_stmListList*, bool> S;

									Temp_tempList* varlist = ssa_variables;
									while (varlist)
									{
										V[varlist->head] = undefined;

										varlist = varlist->tail;
									}

									// The start block is executed
									S[block.stmLists->head] = true;

									// Setup worklists
									Temp_tempList* Wv = NULL;
									{
										Temp_tempList* varlist = ssa_variables;
										while (varlist)
										{
											Wv = new Temp_tempList(varlist->head, Wv);

											varlist = varlist->tail;
										}
									}

									C_stmListListList* Wb = NULL;
									{
										C_stmListListList* blist = block.stmLists;
										while (blist)
										{
											Wb = new C_stmListListList(blist->head, Wb);

											blist = blist->tail;
										}
									}

									while (/*Wv != NULL ||*/ Wb != NULL)
									{
										// Find an executable block

										C_stmListListList* b = Wb;
										while (b && S[b->head] == false)
										{
											b = b->tail;
										}
										if (b == NULL) break;

										Wb = remove_node(Wb, b->head);
										
										// For any executable block B with only one successor C, set S[C] true
										{
											if (b->head->succ && b->head->succ->tail == NULL)
											{
											//	if (S[b])
												{
													S[b->head->succ->head] = true;
													We = new C_stmListListList(b->head->succ->head, We);
												}
											}
										}

										T_StmList* stms = b->head->head;
										while (stms)
										{
								//		Temp_temp** var = Wv->head;
								//		Wv = Wv->tail;

										//T_Stm* defsite = def[var];
											T_Stm* defsite = stms->head;

											if (defsite->kind == T_Stm::T_MOVE && defsite->move.left->kind == T_Exp::T_TEMP)
											{
												Temp_temp** var = defsite->move.left->temp;

												if (defsite->move.right->kind == T_Exp::T_CONST)
												{
													V[var] = defsite->move.right;

													/*
													T_StmList* stmlist = uses[var];
													while (stmlist)
													{


														stmlist = stmlist->tail;
													}
													*/
												}
												else if (defsite->move.right->kind == T_Exp::T_BINOP)
												{
													ASSERT(defsite->move.right->binop.left->kind == T_Exp::T_TEMP);
													ASSERT(defsite->move.right->binop.right->kind == T_Exp::T_TEMP);

													if (V[defsite->move.right->binop.left->temp]->kind == T_Exp::T_CONST &&
														V[defsite->move.right->binop.right->temp]->kind == T_Exp::T_CONST)
													{
														long left_value = V[defsite->move.right->binop.left->temp]->const_int.int32Val;
														long right_value = V[defsite->move.right->binop.right->temp]->const_int.int32Val;

														long value;

														switch (defsite->move.right->binop.op)
														{
														case '+':
															value = left_value + right_value;
															break;

														case '-':
															value = left_value - right_value;
															break;

														case '*':
															value = left_value * right_value;
															break;

														case '/':
															value = left_value / right_value;
															break;

														case '%':
															value = left_value % right_value;
															break;

														case '|':
															value = left_value | right_value;
															break;

														case '&':
															value = left_value & right_value;
															break;

														case '^':
															value = left_value ^ right_value;
															break;

														case '<<':
															value = left_value << right_value;
															break;

														case '>>':
															value = left_value >> right_value;
															break;

														default:
															ASSERT(0);
														}

														V[var] = T_ConstExp(value);
													}

													if (V[defsite->move.right->binop.left->temp] == overdefined || V[defsite->move.right->binop.right->temp] == overdefined)
													{
														V[var] = overdefined;
													}
												}
												else if (defsite->move.right->kind == T_Exp::T_PHI)
												{
													Temp_tempList* temps = defsite->move.right->phi.temps;
													C_stmListListList* preds = defsite->move.right->phi.preds;

													// find the first executable
													while (preds)
													{
														if (S[preds->head] == true)
															break;

														temps = temps->tail;
														preds = preds->tail;
													}

													// if the other preds are non-executable or if those which are
													// executable have the same const, then we replace this ø-function
													// with v <- c

													T_Exp* c = V[temps->head];

													if (c->kind == T_Exp::T_CONST)
													{
														temps = temps->tail;
														preds = preds->tail;

														while (temps)
														{
															if (S[preds->head] == true &&
																(V[temps->head]->kind != T_Exp::T_CONST ||
																V[temps->head]->const_int.int32Val != c->const_int.int32Val))
															{
																break;
															}

															temps = temps->tail;
															preds = preds->tail;
														}

														if (temps == NULL)
														{
															ASSERT(preds == NULL);
															V[var] = c;
														}
														else
														{
															ASSERT(preds != NULL);
															V[var] = overdefined;
														}
													}
												}
												else
													ASSERT(0);
											}

											if (stms->head->kind == T_Stm::T_CJUMP)
												break;

											stms = stms->tail;
										}

										/*
										stms = b->head->head;
										while (stms->tail)
										{
											stms = stms->tail;
										}
										*/

										if (stms && stms->head->kind == T_Stm::T_CJUMP)
										{
											T_Stm* cjump = stms->head;

										//	ASSERT(cjump->cjump.left->kind == T_Exp::T_TEMP);
										//	ASSERT(cjump->cjump.right->kind == T_Exp::T_TEMP);

											if ((cjump->cjump.left->kind != T_Exp::T_CONST && V[cjump->cjump.left->temp] == overdefined) ||
												(cjump->cjump.right->kind != T_Exp::T_CONST && V[cjump->cjump.right->temp] == overdefined))
											{
												ASSERT(0);
											}

											if ((cjump->cjump.left->kind == T_Exp::T_CONST || V[cjump->cjump.left->temp]->kind == T_Exp::T_CONST) &&
												(cjump->cjump.right->kind == T_Exp::T_CONST || V[cjump->cjump.right->temp]->kind == T_Exp::T_CONST))
											{
												bool result;

												long left_value = (cjump->cjump.left->kind == T_Exp::T_CONST? cjump->cjump.left: V[cjump->cjump.left->temp])->const_int.int32Val;
												long right_value = (cjump->cjump.right->kind == T_Exp::T_CONST? cjump->cjump.right: V[cjump->cjump.right->temp])->const_int.int32Val;

												switch (cjump->cjump.relop)
												{
												case '==':
													result = left_value == right_value;
													break;

												case '!=':
													result = left_value != right_value;
													break;

												case '>':
													result = left_value > right_value;
													break;

												case '<':
													result = left_value < right_value;
													break;

												case '>=':
													result = left_value >= right_value;
													break;

												case '<=':
													result = left_value <= right_value;
													break;

												default:
													ASSERT(0);
												}

												if (result)
												{
													C_stmListList* b = block.labels[cjump->cjump.t];
													S[b] = true;
													We = new C_stmListListList(b, We);
												}
												else
												{
													C_stmListList* b = block.labels[cjump->cjump.f];
													S[b] = true;
													We = new C_stmListListList(b, We);
												}
											}
										}

										// For any executable block B with only one successor C, set S[C] true

										/*
										C_stmListList* b = Wb;
										while (b)
										{
											if (b->succ->tail == NULL)
											{
												if (S[b])
												{
													S[b->succ->head] = true;
												}
											}

											b = b->tail;
										}
										*/
									}

									{
										Temp_tempList* varlist = ssa_variables;
										while (varlist)
										{
											Temp_temp** var = varlist->head;

											if (V[var]->kind == T_Exp::T_CONST)
											{
												T_Stm* defsite = def[var];
												defsite->kind = T_Stm::T_NULL;

												T_StmList* uselist = uses[var];
												expRefList* exprefs = tempuses_exprefs[var];

												while (uselist)
												{
													uses[var] = remove_node(uses[var], uselist->head);
													stm_uses[uselist->head] = remove_node(stm_uses[uselist->head], var);

													uselist = uselist->tail;
												}

												while (exprefs)
												{
													*(exprefs->head) = V[var];

													//uses[var] = remove_node(uses[var], use

													exprefs = exprefs->tail;
												}

												/*
												while (uselist)
												{
													T_Stm* usestm = uselist->head;

													if (usestm->kind == T_Stm::T_MOVE)
													{
														if (usestm->move.right->kind == T_Exp::T_BINOP)
														{
															ASSERT(0);
														}
														else
															ASSERT(0);
													}
													else if (usestm->kind == T_Stm::T_CJUMP)
													{
														if (usestm->cjump.left->kind == T_Exp::T_TEMP && usestm->cjump.left->temp == var)
														{
															usestm->cjump.left = V[var];
														}

														if (usestm->cjump.right->kind == T_Exp::T_TEMP && usestm->cjump.right->temp == var)
														{
															usestm->cjump.right = V[var];
														}
													}
													else
														ASSERT(0);

													uselist = uselist->tail;
												}
												*/
											}

											varlist = varlist->tail;
										}
									}

									We = Reverse(We);

									printf("***conditional constant propagation***************\n");
									{
										C_stmListListList* b = We;
										while (b)
										{
											print(b->head->head);

											b = b->tail;
										}
									}
								}
							{

	#if 0
							//	printf("**************************************\n");
							//	print(pDeclarator->m_statementList);

								// change those temps that are taken addressof into a5+offset (into frame)
								{
									int changed = change(pDeclarator, pDeclarator->m_statementList);

									printf("********* change ************************\n");
									print(pDeclarator->m_statementList);

									if (changed)
									{
										def.clear();
										uses.clear();
										stm_uses.clear();

										T_StmList* nlist = NULL;

										T_StmList* slist = pDeclarator->m_statementList;
										while (slist)
										{
											nlist = Reverse(linear(do_stm(slist->head), NULL), nlist);

											slist = slist->tail;
										}

										pDeclarator->m_statementList = Reverse(nlist);

										printf("********* change ************************\n");
										print(pDeclarator->m_statementList);

										ssa_rename(pDeclarator->m_statementList);
									}
								}
	#endif

	#if 0
								int changed;
								do
								{
									changed = 0;

									/*
									changed += common_subexpression_removal(pDeclarator->m_statementList);
									printf("********* common_subexpression_removal ************************\n");
									print(pDeclarator->m_statementList);
									*/

									changed += const_copy_propagation(pDeclarator->m_statementList);
									printf("********* const_copy_propagation ************************\n");
									print(pDeclarator->m_statementList);

									changed += remove_dead_code(pDeclarator->m_statementList);
									printf("********* remove_dead_code ************************\n");
									print(pDeclarator->m_statementList);
								}
								while (changed);

								/*
								printf("************** 1 ************************\n");
								print(pDeclarator->m_statementList);

								{
									common_subexpression_removal(pDeclarator->m_statementList);
								}
								*/

							//	printf("************** 2 ************************\n");
							//	print(pDeclarator->m_statementList);

								do
								{
									changed = 0;

									changed += unfolding(pDeclarator->m_statementList);
									printf("************** unfolding ************************\n");
									print(pDeclarator->m_statementList);

									changed += remove_dead_code(pDeclarator->m_statementList);
									printf("********* remove_dead_code ************************\n");
									print(pDeclarator->m_statementList);
								}
								while (changed);
	#endif

								{
									from_ssa(We);

								//	printf("********* from_ssa ************************\n");
								//	print(pDeclarator->m_statementList);
								}

								{
									T_StmList* stmlist = NULL;	// The trace (start out empty)

									C_stmListListList* stmlists = We;//block.stmLists;
									while (stmlists->tail)
									{
										T_StmList* stms = stmlists->head->head;
										while (stms->tail)
										{
											stmlist = new T_StmList(stms->head, stmlist);

											stms = stms->tail;
										}

										ASSERT(stmlists->tail->head->head->head->kind == T_Stm::T_LABEL);	// The next block must start with a label statement

										if (stms->head->kind == T_Stm::T_JUMP)
										{
											if (stms->head->jump.labels->head == stmlists->tail->head->head->head->label &&	// Jumps to next statement
												stms->head->jump.labels->tail == NULL)	// and ONLY to next statement
											{
												// Skip the jump
											}
											else
											{
												stmlist = new T_StmList(stms->head, stmlist);	// Include the jump
											}
										}
										else if (stms->head->kind == T_Stm::T_CJUMP)
										{
											if (stmlists->tail->head->head->head->label == stms->head->cjump.t)
											{
												// If followed by true label, negate the condition and switch t and f
												stmlist = new T_StmList(
													T_CJumpStm(not_relop(stms->head->cjump.relop),
														stms->head->cjump.left, stms->head->cjump.right,
														stms->head->cjump.f, stms->head->cjump.t),
													stmlist);
											}
											else
											{
												stmlist = new T_StmList(stms->head, stmlist);	// Include the cjump

												if (stmlists->tail->head->head->head->label != stms->head->cjump.f)
												{
													// If not followed by false label, append a statement that jumps to false label
													stmlist = new T_StmList(T_JumpStm(T_Name(stms->head->cjump.f), new Temp_labelList(stms->head->cjump.f, NULL)), stmlist);
												}
											}
										}
										else
										{
											// last statement of basic block must be either JUMP or CJUMP
											ASSERT(0);
										}

										stmlists = stmlists->tail;
									}

									stmlist = new T_StmList(T_Label(pDeclarator->epilogue_label), stmlist);
									pDeclarator->m_statementList = Reverse(stmlist);
								}

								printf("**************************************\n");
								print(pDeclarator->m_statementList);
							}

							//if (pDeclarator->m_pType->GetType()->m_type == type_function)
							CFunctionCode* pFunctionCode;

							print(pDeclarator->m_statementList);

							//	unquadruple(pDeclarator->m_statementList)

								if (true)//pDeclarator->m_pBody)
								{
									do
									{
										printf("**************************************\n");
										printf("**************************************\n");

										spillnodes = NULL;
										graph = NULL;
										pFunctionCode = new CFunctionCode;

	#if 0
										pFunctionCode->emit(AS_Label(pDeclarator->m_tempLabel));
										pFunctionCode->emit(AS_Fun(pDeclarator));
										pFunctionCode->emit(AS_LBrac());
			#if 0
										pFunctionCode->emit(AS_Line(pDeclarator/*->m_pBody*/->line_pos));
			#endif
	#endif

										pCodeGen->Function_Prologue(pFunctionCode);

										// Instruction selection
										{
											T_StmList *p = pDeclarator->/*m_pBody->*/m_statementList;
											while (p)
											{
											//	ASSERT(p->kind == T_Stm::TS_SEQ);
												pCodeGen->WriteStatement(pFunctionCode, p->head);

												p = p->tail;
											}
										}

										// Control flow graph
										//use[] and def[] on each node

								//		pFunctionCode->emit(AS_Line(pDeclarator->m_last_line));

										pCodeGen->Function_Epilogue(pFunctionCode);

								//		pFunctionCode->emit(AS_RBrac());

										if (true)
										{
											AS_instrList* il = pFunctionCode->instrList;

											G_Node* live = Liveness(il);

											printf("\n");

											G_Node* n = live;

											{
												Temp_tempList* inlist = n->in;
												while (inlist)
												{
													printf("Usage of uninitialized variable %s\n", (*inlist->head)->name);

													inlist = inlist->tail;
												}

												/*
												tl = n->instr->OPER.src;
												printf("\tuse: ");
												while (tl)
												{
													 printf("%s, ", tl->temp->name);
												//	if (!find(n->in, tl->temp))
												//	{
												//		printf("Usage of uninitialized variable\n");
												//	}
													tl = tl->tail;
												}

												tl = n->in;
												printf("\tlive-in: ");
												while (tl)
												{
													 printf("%s, ", tl->temp->name);
												//	if (!find(n->in, tl->temp))
												//	{
												//		printf("Usage of uninitialized variable\n");
												//	}
													tl = tl->tail;
												}

												tl = n->out;
												printf("\tlive-out: ");
												while (tl)
												{
													 printf("%s, ", tl->temp->name);
												//	if (!find(n->in, tl->temp))
												//	{
												//		printf("Usage of uninitialized variable\n");
												//	}
													tl = tl->tail;
												}

												printf("\n");

												n = n->succ;
												*/
											}

		#if 0
											compile::Node* n = live;
											while (n)
											{
												Temp_tempList* tl;

												tl = n->instr->OPER.dst;
												printf("def: ");
												while (tl)
												{
													 printf("%s, ", tl->temp->name);
												//	if (!find(n->in, tl->temp))
												//	{
												//		printf("Usage of uninitialized variable\n");
												//	}
													tl = tl->tail;
												}

												tl = n->instr->OPER.src;
												printf("\tuse: ");
												while (tl)
												{
													 printf("%s, ", tl->temp->name);
												//	if (!find(n->in, tl->temp))
												//	{
												//		printf("Usage of uninitialized variable\n");
												//	}
													tl = tl->tail;
												}

												tl = n->in;
												printf("\tlive-in: ");
												while (tl)
												{
													 printf("%s, ", tl->temp->name);
												//	if (!find(n->in, tl->temp))
												//	{
												//		printf("Usage of uninitialized variable\n");
												//	}
													tl = tl->tail;
												}

												tl = n->out;
												printf("\tlive-out: ");
												while (tl)
												{
													 printf("%s, ", tl->temp->name);
												//	if (!find(n->in, tl->temp))
												//	{
												//		printf("Usage of uninitialized variable\n");
												//	}
													tl = tl->tail;
												}

												printf("\n");

												n = n->succ;
											}
		#endif

											if (m_exeType == 1)
											{
												Live_gtemp* gtemps[16];

												for (int i = 0; i < 16; i++)
												{
													Live_gtemp* gtemp = new Live_gtemp;
													gtemp->temp = regs[i];
													graph = new Live_gtempList(gtemp, graph);

													gtemps[i] = gtemp;
												}

												for (int i = 0; i < 16; i++)
												{
													Live_gtemp* gtemp = gtemps[i];

													for (int j = i+1; j < 16; j++)
													{
														G_addEdge(gtemp, gtemps[j]);
													}
												}


												/*
												Live_gtemp* gtemp_d1 = new Live_gtemp;
												gtemp_d1->temp = d1;
												graph = new Live_gtempList(gtemp_d1, graph);

												Live_gtemp* gtemp_d1 = new Live_gtemp;
												gtemp_d1->temp = d1;
												graph = new Live_gtempList(gtemp_d1, graph);

												Live_gtemp* gtemp_d1 = new Live_gtemp;
												gtemp_d1->temp = d1;
												graph = new Live_gtempList(gtemp_d1, graph);

												Live_gtemp* gtemp_a0 = new Live_gtemp;
												gtemp_a0->temp = a0;
												graph = new Live_gtempList(gtemp_a0, graph);

												Live_gtemp* gtemp_a5 = new Live_gtemp;
												gtemp_a5->temp = a5;
												graph = new Live_gtempList(gtemp_a5, graph);

												Live_gtemp* gtemp_a6 = new Live_gtemp;
												gtemp_a6->temp = a6;
												graph = new Live_gtempList(gtemp_a6, graph);

												G_addEdge(gtemp_d0, gtemp_a0);
												G_addEdge(gtemp_d0, gtemp_a5);
												G_addEdge(gtemp_d0, gtemp_a6);

												G_addEdge(gtemp_a0, gtemp_a5);
												G_addEdge(gtemp_a0, gtemp_a6);

												G_addEdge(gtemp_a5, gtemp_a6);
												*/
											}
											else
											{
												Live_gtemp* gtemp_eax = new Live_gtemp;
												gtemp_eax->temp = eax;
												graph = new Live_gtempList(gtemp_eax, graph);

												Live_gtemp* gtemp_edx = new Live_gtemp;
												gtemp_edx->temp = edx;
												graph = new Live_gtempList(gtemp_edx, graph);

												Live_gtemp* gtemp_ebp = new Live_gtemp;
												gtemp_ebp->temp = ebp;
												graph = new Live_gtempList(gtemp_ebp, graph);

												G_addEdge(gtemp_eax, gtemp_edx);
												G_addEdge(gtemp_eax, gtemp_ebp);
												G_addEdge(gtemp_edx, gtemp_ebp);
											}

											Interference(live);
											if (graph)
											{
												Live_gtempList* g = graph;

												printgraph(g);
												printf("\n");

												int K = 16;

												while (g)
												{
													int count = G_count(g);

													g = Simplify(g, K);

													g = Coalesce(g, il, K);

													int count2 = G_count(g);

													if (count == count2)
													{
														// Freeze a low-degree node

														Live_gtempList* g2 = g;

														while (g2)
														{
															Live_gtemp* m = g2->head;
															int adjcount = G_count(m->adj);
															if (adjcount < K && !m->temp->m_precolored)
															{
																m->bMoveRelated = 0;
																break;
															}

															g2 = g2->tail;
														}

														if (g2 == NULL)
														{
															// If there are no low-degree nodes, potential spill
															printf("Potential spill\n");

															Live_gtemp* m = g->head;

															// Remove m from the adjacent nodes of m, but don't do the opposite,
															// as we need to remember the adjacent nodes of m, so we can reinsert it later
															Live_gtempList* adj = m->adj;
															while (adj)
															{
																adj->head->adj = G_rmTemp(adj->head->adj, m);
																adj = adj->tail;
															}
															g = G_rmTemp(g, m);

															gstack.push(m);
															//g = g->tail;

															printgraph(g);
															printf("\n");
														}
													}

												//	compile::printgraph(g);
												//	printf("\n");
												}

												printf("****************\n");
												Select(K);
											}
										}

										{
											Live_gtempList* spill = spillnodes;
											while (spill)
											{
												{
													T_StmList *p = pDeclarator->/*m_pBody->*/m_statementList;
													while (p)
													{
													//	ASSERT(p->kind == T_Stm::TS_SEQ);
													//	pCodeGen->WriteStatement(pFunctionCode, p->head);

														replace(p->head, spill->head->temp, spill->head->temp->m_exp);

														p = p->tail;
													}
												}

												spill = spill->tail;
											}
										}

									}
									while (spillnodes);

									pFunctionCode = new CFunctionCode;

									// Instruction selection
									{
										T_StmList *p = pDeclarator->/*m_pBody->*/m_statementList;
										while (p)
										{
										//	ASSERT(p->kind == T_Stm::TS_SEQ);
											pCodeGen->WriteStatement2(pFunctionCode, p->head);

											p = p->tail;
										}
									}

									pCode->emit(AS_Label(pDeclarator->m_tempLabel));
									pCode->emit(AS_Align(2));
									pCode->emit(AS_Fun(pDeclarator));
									pCode->emit(AS_LBrac());
		#if 0
									pFunctionCode->emit(AS_Line(pDeclarator/*->m_pBody*/->line_pos));
		#endif

									pCodeGen->Function_Prologue(pCode);

									AS_instrList* il = pFunctionCode->instrList;
									while (il)
									{
										if (!(il->head->kind == AS_instr::I_MOVE &&
											(*il->head->MOVE.src->head)->getn() == (*il->head->MOVE.dst->head)->getn()))
										{
											pCode->emit(il->head);
										}

										il = il->tail;
									}

										pCode->emit(AS_Line(pDeclarator->m_last_line));

										pCodeGen->Function_Epilogue(pCode);

										pCode->emit(AS_RBrac());

									delete pFunctionCode;
								}

							}

							for (uint i = 0; i < pDeclarator->m_data.size(); ++i)
							{
								T_Data* data = pDeclarator->m_data[i];

								pCode->emit(AS_Label(data->m_label));
								pCode->emit(AS_Data(data->m_data, data->m_len));
							}
						}
						else
						{
							pCode->emit(AS_Label(pDeclarator->m_tempLabel));

							pCode->emit(AS_Data2(pDeclarator->m_texplist));

							//pCode->emit(AS_Data(pDeclarator->data->m_data, data->m_len));
						}
					}
					else
					{
						pCode->emit(AS_Fun(pDeclarator));
					}
				}
			}

			{
				CObjectFile* pObjectFile;
				if (false)
				{
					pObjectFile = new CCOFFObjectFile;
				}
				else
				{
					pObjectFile = new CAOut;
				}

				pObjectFile->Create(fileout, pGlobal, pGlobalScope, tglobals, pCode, pCodeGen->m_processor_id);

				delete pObjectFile;
			}

			fclose(fileout);
		}
		else
		{
			printf("Failed to open output file\n");
		}
	}

}

}
}
