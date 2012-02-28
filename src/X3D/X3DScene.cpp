#include "StdAfx.h"
#include "X3D2.h"
#include "X3DScene.h"
#include "Group.h"
#include "Layer.h"
#include "NavigationInfo.h"
#include "VRMLLoader.h"

#include "GUI/OleDataObject.h"

namespace System
{
using namespace IO;

void Register(Type* pType, Object* instance)
{
	ClassType* pClassType = pType->AsClass();

	pClassType->m_instances.m_list.push_back(instance);
}

namespace x3d
{

///////////////////////////////////////////////////////////////////////////////

//#define REMAINDER(t, d) ((t) - (d)*floor((t)/(d)))

#if 0
void glTranslate(gmVector2f& v)
{
	::glTranslatef(v[0], v[1], 0);
}

void glTranslate(gmVector3t<float>& v)
{
	::glTranslatef(v[0], v[1], v[2]);
}

void glTranslate(gmVector3t<double>& v)
{
	::glTranslated(v[0], v[1], v[2]);
}

void glScale(gmVector2f& v)
{
	::glScalef(v[0], v[1], 1);
}

void glScale(gmVector3t<float>& v)
{
	::glScalef(v[0], v[1], v[2]);
}

void glScale(gmVector3t<double>& v)
{
	::glScaled(v[0], v[1], v[2]);
}

void glRotate(float angle)
{
	::glRotatef(angle, 0, 0, 1);
}

void glRotate(float angle, gmVector3t<float>& v)
{
	::glRotatef(angle, v[0], v[1], v[2]);
}

void glRotate(float angle, gmVector3t<double>& v)
{
	::glRotated(angle, v[0], v[1], v[2]);
}

void glVertex2(gmVector2f& v)
{
	::glVertex2d(v[0], v[1]);
}

void glVertex3(gmVector3t<float>& v)
{
	::glVertex3f(v[0], v[1], v[2]);
}

void glVertex3(gmVector3t<double>& v)
{
	::glVertex3d(v[0], v[1], v[2]);
}

void glNormal3(gmVector3t<float>& v)
{
	::glNormal3f(v[0], v[1], v[2]);
}

void glNormal3(gmVector3t<double>& v)
{
	::glNormal3d(v[0], v[1], v[2]);
}

void glColor3(gmVector3t<float>& v)
{
	::glColor3f(v[0], v[1], v[2]);
}

#endif

ProfileDeclaration::ProfileDeclaration(StringIn name) : m_name(name)
{
}

///////////////////////////////////////////////////////////////////////////
// ExecutionContext

EncodingID X3DExecutionContext::getEncoding()
{
	return m_encoding;
}

///////////////////////////////////////////////////////////////////////////
// X3DScene

X3DScene::X3DScene()
{
//	m_root = NULL;
	m_encoding = Encoding_Scripted;	// May be overwritten later
	m_version = nullptr;

	m_root = new Layer;
	m_root->m_ownerLayer = m_root;	// hm.. ??
	m_root->m_scene = this;

	X3DByType_avl::init_header(&m_nodesByTypeHeader);
#if 0
	int i = 0;
	while (nodeTypes[i].nodeName)
	{
		SAINodeType* pNodeType = new SAINodeType;
	//	pNodeType->m_pScene = this;

		pNodeType->m_p = &nodeTypes[i];

		int j = 0;
		while (pNodeType->m_p->fields[j].fieldName)
		{
			X3DFieldDefinition* pFieldDefinition = new X3DFieldDefinition;
			pFieldDefinition->m_p = &pNodeType->m_p->fields[j];

			pNodeType->m_fieldDefinitions->m_items.Add(pFieldDefinition);

			j++;
		}

		m_nodeTypes.Add(pNodeType);

		i++;
	}
#endif

	Register(typeid(X3DScene), this);
}

X3DScene::~X3DScene()
{
	/*
	if (m_root)
	{
		delete m_root;
		m_root = NULL;
	}
	*/

	{
		for (size_t i = 0; i < m_protoDeclarations.GetSize(); i++)
		{
			delete m_protoDeclarations[i];
		}
		m_protoDeclarations.RemoveAll();
	}

	{
		for (size_t i = 0; i < m_routes.GetSize(); i++)
		{
			delete m_routes[i];
		}
		m_routes.RemoveAll();
	}
}

SAIProtoDeclaration* X3DScene::FindProto(StringIn name)
{
	for (unsigned int i = 0; i < m_protoDeclarations.GetSize(); i++)
	{
		if (m_protoDeclarations[i]->m_name == name)
		{
			return m_protoDeclarations[i];
		}
	}
	return nullptr;
}

X3DNode* X3DScene::getNamedNode(StringIn name) throw (InvalidNodeException*)
{
	for (uint i = 0; i < m_defs.size(); ++i)
	{
		if (m_defs[i]->m_name == name)
		{
			return m_defs[i]->m_node;
		}
	}

	raise(InvalidNodeException(name));
	return nullptr;
}

void X3DScene::AddNode(X3DNode* node)
{
	if (node->m_scene != this)
	{
		node->m_scene = this;

		CriticalSectionLock lock(m_nodesByTypeHeaderCS);
		m_nodes.push_back(node);
		X3DByType_avl::insert_equal_lower_bound(&m_nodesByTypeHeader, node, X3DNode_compareByType());
	}
}

X3DNode* X3DScene::CreateNodeOfType(NodeType* pNodeType)
{
	VERIFY(pNodeType);

	X3DNode* node = pNodeType->CreateNode();
	if (node)
	{
		AddNode(node);

		/*
		X3DLightNode* light = dynamic_cast<X3DLightNode*>(node);
		if (light)
		{
			m_lights.Add(light);
		}
		*/
	}

	return node;
}

X3DNode* X3DScene::createNode(StringIn name)
{
	NodeType* pNodeType = NodeType::FindByName(name);
	if (pNodeType)
	{
		return CreateNodeOfType(pNodeType);
	}
	else
	{
		return nullptr;
	}
}

SAIProtoDeclaration* X3DScene::getProtoDeclaration(StringIn name)
{
	for (auto it = m_protoDeclarations.begin(); it != m_protoDeclarations.end(); ++it)
	{
		if ((*it)->m_name == name)
		{
			return (*it);
		}
	}

	return nullptr;
}

MFNode* X3DScene::getRootNodes()
{
	if (m_root)
	{
		return m_root->getChildrenField();
	}

	return nullptr;
}

void X3DScene::removeRootNode(X3DNode* node)
{
	MFNode* children = m_root->getChildrenField();
	for (int i = children->m_items.size()-1; i >= 0; --i)
	{
		if (children->m_items[i] == node)
		{
			// TODO
			ASSERT(0);
			//children->remove1Value();
		}
	}

	/*
	for (int i = 0; i < node->m_parents.size(); ++i)
	{
		if (node->m_parents[i] == children)
		{

		}
	}
	*/
}

String X3DScene::getMetadata(StringIn key)
{
	return m_metadata.find(key)->second;
}

void X3DScene::setMetadata(StringIn key, StringIn value)
{
	m_metadata[key] = value;
}

String X3DScene::ToString()
{
	IO::StringWriter stream;
	WriteVRML(stream);
	return stream.str();
}

IO::TextWriter& X3DScene::WriteVRML(IO::TextWriter& stream)
{
// VRML encoding

	stream << "#X3D ";
	stream << "V" << getSpecificationVersion() << " ";
	stream << "utf8";
	stream << endl;

	stream << "PROFILE " << "Interchange" << endl;

	for (auto it = m_metadata.begin(); it != m_metadata.end(); ++it)
	{
		stream << "META " << doublequote(it->first) << " " << doublequote(it->second) << endl;
	}
	stream << endl;

	MFNode* nodes = getRootNodes();
	if (nodes)
	{
		size_t count = nodes->get_size();
		for (size_t i = 0; i < count; ++i)
		{
			X3DNode* node = nodes->get1Value(i);

			node->WriteVRML(stream);
		}
	}

// TODO: Routes

	return stream;
}

void X3DScene::addRoute(Route* route)
{
	m_routes.push_back(route);
}

void X3DScene::addRoute(X3DNode* sourceNode, StringIn sourceField, X3DNode* destinationNode, StringIn destinationField)
{
	if (sourceNode == nullptr) raise(ArgumentNullException());
	if (destinationNode == nullptr) raise(ArgumentNullException());
	if (sourceField.GetLength() == 0) raise(X3DException(S(L"sourceField->Length() == 0")));
	if (destinationField.GetLength() == 0) raise(X3DException(S(L"destinationField->Length() == 0")));

	X3DField* pSourceField = sourceNode->getField(sourceField);
	X3DField* pDestinationField = destinationNode->getField(destinationField);

	if (pSourceField == nullptr)
	{
		raise(X3DException(S(L"source Field not found")));
	}

	if (pDestinationField == nullptr)
	{
		raise(X3DException(S(L"destination Field not found")));
	}

	Route* pRoute = new Route(new FieldBinding(pSourceField), pDestinationField);

	/*
	pRoute->m_sourceNode = sourceNode;
	pRoute->m_sourceField = pSourceField;

	pRoute->m_destination = new RouteDestination(destinationNode, pDestinationField);
//	pRoute->m_destinationNode = destinationNode;
//	pRoute->m_destinationField = pDestinationField;
*/

	pSourceField->m_outputRoutes.Add(pRoute);
	pDestinationField->m_inputRoute = pRoute;

	addRoute(pRoute);
}

bool X3DScene::Load(StringIn url)
{
	if (url == nullptr)
	{
		raise(ArgumentNullException());
	}

	m_overList.clear();
	m_protoDeclarations.clear();
	m_routes.clear();
	m_defs.clear();
//	LayerSet* m_layerSet;
//	Gui::Clock* m_clock;
	m_nodes.clear();
//	vector<X3DLightNode*, __gc_allocator> m_lights;
	m_namedNodes.clear();

	m_root = nullptr;	// TODO

	m_url = url;

	Net::UrlBinding binding;
	_Ptr<IO::Stream> stream = binding.BindToObject(url, nullptr);

	VRMLLoader loader;
	bool success = (loader.ParseInto(this, stream) == 0);
	return success;
}

#if 0
ErrorCode X3DScene::readStream(ISequentialByteStream* stream)
{
	ErrorCode hr = Error;	// Assume error

	ASSERT(0);

#if 0
#if 0
	// Create root group
	SAINodeType* pGroupType = FindNodeType(WSTR("Group"));
	CComPtr<ILX3DNode> root = pGroupType->CreateNodeOfType();
	m_root = static_cast<<CLGroup>*>(root.p);
#endif

	_bstr_t url = m_url;
	LPTSTR ext = PathFindExtension(url);

	if (ext && !strcmp(ext, ".iob"))
	{
		CComPtr<ILX3DLoader> loader;
		loader.CoCreateInstance(WSTR("LImagine.TDDDLoader"));
		if (loader)
		{
			loader->Load(stream, this, static_cast<MFNode*>(m_root->m_children));
		}
	}
	else if (ext && !strcmp(ext, ".c4d"))
	{
		CComPtr<ILX3DLoader> loader;
		loader.CoCreateInstance(WSTR("LCinema4D.DOK5Loader"));
		if (loader)
		{
			loader->Load(stream, this, static_cast<MFNode*>(m_root->m_children));
		}
	}
	else if (ext &&
		(!strcmp(ext, ".lw") || !strcmp(ext, ".lwo")))
	{
		CComPtr<ILX3DLoader> loader;
		loader.CoCreateInstance(WSTR("LLWO.LWOLoader"));
		if (loader)
		{
			loader->Load(stream, this, static_cast<MFNode*>(m_root->m_children));
		}
	}
	else
	{
		CComPtr<ITextData> textData;
		if (SUCCEEDED(textData.CoCreateInstance(CLSID_TextData)))
		{
			<IPersistStream> persistStream = textData;
			persistStream->Load(stream);

			BSTR buffer;
			textData->get_data(&buffer);

			textData->save(WSTR("c:\\last_vrml.wrl"));

		#if 0
			BYTE buffer[5] = {0};
			ULONG nRead;
			stream->Read(buffer, 5, &nRead);

			// Seek back to beginning
			LARGE_INTEGER li;
			li.QuadPart = 0;
			stream->Seek(li, STREAM_SEEK_SET, NULL);
		#endif

			if (	!wcsncmp(buffer, WSTR("#X3D"), 4) ||
					!wcsncmp(buffer, WSTR("#VRML"), 5))
			{
				m_encoding = Encoding_VRML;

				CVRMLParser* pParser = new CVRMLParser;

	//			pParser->m_pBrowser = this;
				pParser->m_scene = this;

				/*
				ULARGE_INTEGER size;

				LARGE_INTEGER li;
				li.QuadPart = 0;
				stream->Seek(li, STREAM_SEEK_END, &size);

				stream->Seek(li, STREAM_SEEK_SET, NULL);

				pParser->m_buflength = (ULONG)size.QuadPart;

				LPBYTE buffer = (LPBYTE)malloc(pParser->m_buflength);
				if (buffer)
				{
					pParser->m_buffer = (WCHAR*)malloc((pParser->m_buflength+1)*2);
					if (pParser->m_buffer)
					{
						pParser->m_buffer[pParser->m_buflength] = 0;	// null-terminated

						stream->Read(buffer, pParser->m_buflength, NULL);

						for (int i = 0; i < pParser->m_buflength; i++)
						{
							pParser->m_buffer[i] = buffer[i];
						}
					}

					free(buffer);
				}
				*/
				pParser->m_buflength = SysStringLen(buffer);
				pParser->m_buffer = buffer;

				hr = pParser->ParseWorld();

				pParser->m_buffer = NULL;
				delete pParser;
			}
			else
			{
		#if 0
			// Try as xml (x3d) file
				CComPtr<ILDOMDocument> document;
				if (SUCCEEDED(document.CoCreateInstance(CLSID_LDOMDocument)))
				{
					VARIANT_BOOL success;
					document->load(_variant_t(stream), &success);
					if (success)
					{
						CComPtr<ILDOMElement> documentElement;
						document->get_documentElement(&documentElement);
						if (documentElement)
						{
							CComPtr<ILDOMElement> sceneElement = FindByTagName(documentElement, L"X3DScene", FALSE);
							if (sceneElement)
							{
								pScene->m_root = BuildScene(sceneElement);
							}

							pScene->m_encoding = Encoding_XML;

							*pVal = pScene;
							(*pVal)->AddRef();
							hr = S_OK;	// Valid xml, so we don't return error
						}
					}
				}
		#endif
			}
		}
	}
#endif

	return hr;
}
#endif

#if 0
ErrorCode STDMETHODCALLTYPE X3DScene::IsDirty( void)
{
	return S_FALSE;
}

// IPersistMoniker
STDMETHODIMP X3DScene::Load( 
      /* [in] */ BOOL fFullyAvailable,
      /* [in] */ IMoniker *pimkName,
      /* [in] */ LPBC pibc,
      /* [in] */ DWORD grfMode)
{
	m_curMoniker = pimkName;

	LPWSTR szDisplayName;
	m_curMoniker->GetDisplayName(pibc, NULL, &szDisplayName);
	m_url = szDisplayName;
	CoTaskMemFree(szDisplayName);

//	CComPtr<IStream> stm;
//	pimkName->BindToStorage(pibc, NULL, IID_IStream, (void**)&stm);

	ErrorCode hr = E_FAIL;	// Assume error

#if 0
	CComPtr<IBindCtx> bctx;
	if (SUCCEEDED(CreateBindCtx(0/*reserved*/, &bctx)))
	{
#endif
		CComPtr<IStream> stream;
		hr = pimkName->BindToStorage(pibc, NULL, IID_IStream, (void**)&stream);
		if (stream)
		{
			hr = readStream(stream);
		}

#if 0
	//CComPtr<ITextData> textData;
	hr = m_textData.CoCreateInstance(CLSID_TextData);
	if (SUCCEEDED(hr))
	{
		<IPersistMoniker> persistMoniker = m_textData;
		hr = persistMoniker->Load(fFullyAvailable, pimkName, pibc, grfMode);

		if (SUCCEEDED(hr))
		{
		//	<IPersistStream> persistStream = textData;
		//	persistStream->Load(stm);

			//CComPtr<ILDOMImplementation> impl;
			//impl.CoCreateInstance(CLSID_LDOMImplementation);
			//if (impl)
			{
				//CComPtr<ILDOMBuilder> builder;
				//impl->createDOMBuilder(0, NULL, &builder);

				//builder->set_errorHandler(m_errorHandler);	// Not standard ?

				CDOMParser parser;

				parser.m_activeDocument = this;
				parser.m_errorHandler = m_errorHandler;
				parser.m_textDoc = m_textData;
				m_textData->get_url(&parser.m_uri);
				parser.loadXML2();

				CComPtr<ILDOMDocument> document = parser.m_document;

				/*
				*pVal = parser.m_document;
				if (*pVal) (*pVal)->AddRef();


				*pVal = parser.m_document;

				builder->parseTextData(m_textData, &document);
				*/

				SetDocument(document);

				if (FALSE)
				{
					StartPlay();
				}
			}
		}
	}
#endif

	return hr;
}

STDMETHODIMP X3DScene::Save( 
      /* [in] */ IMoniker *pimkName,
      /* [in] */ LPBC pbc,
      /* [in] */ BOOL fRemember)
{
	return S_OK;
}

STDMETHODIMP X3DScene::SaveCompleted( 
      /* [in] */ IMoniker *pimkName,
      /* [in] */ LPBC pibc)
{
	return S_OK;
}

STDMETHODIMP X3DScene::GetCurMoniker(/* [out] */ IMoniker **ppimkName)
{
	if (ppimkName == NULL) return E_POINTER;
	*ppimkName = m_curMoniker;
	if (*ppimkName) (*ppimkName)->AddRef();
	return S_OK;
}
#endif

void X3DScene::OnTick(double tim)
{
	X3DViewpointNode* viewpoint = get_Viewpoint();
	NavigationInfo* navigationInfo = get_NavigationInfo();

	if (viewpoint && navigationInfo)
	{
		float speed = navigationInfo->getSpeed();
		Vec3f position = viewpoint->getPosition();
		Rotation orientation = viewpoint->getOrientation();

		if (false)
		{
			D3DXMATRIX m;
			D3DXMatrixRotationAxis(&m, (D3DXVECTOR3*)&orientation.m_axis, orientation.m_angle);

			Vec3f front(m._31, m._32, m._33);

			position += front* (speed / m_fps);

			viewpoint->setPosition(position);
		}
	}

	for (size_t i = 0; i < m_nodes.size(); ++i)
	{
		X3DNode* node = m_nodes[i];

	//	CComQIPtr<ILX3DTimeDependentNode> timeDependant = node;
	//	if (timeDependant)
		{
			node->DoTime(tim/*m_currentVideoTime*/);
		}
	}

	m_root->UpdatePos();
}

X3DViewpointNode* X3DScene::get_Viewpoint()
{
	if (m_root->m_viewpointStack.size())
		return m_root->m_viewpointStack.top();
	else
		return nullptr;
}

X3DBackgroundNode* X3DScene::get_Background()
{
	if (m_root->m_backgroundStack.size())
		return m_root->m_backgroundStack.top();
	else
		return nullptr;
}

NavigationInfo* X3DScene::get_NavigationInfo()
{
	if (m_root->m_navigationinfoStack.size())
		return m_root->m_navigationinfoStack.top();
	else
		return nullptr;
}

Fog* X3DScene::get_Fog()
{
	if (m_root->m_fogStack.size())
		return m_root->m_fogStack.top();
	else
		return nullptr;
}

String X3DScene::getSpecificationVersion()
{
	return m_version;
}

String X3DScene::getWorldURL()
{
	return m_url;
}

X3DNode* X3DScene::NodeByType(StringIn nodeType) throw()
{
	CriticalSectionLock lock(m_nodesByTypeHeaderCS);

	X3DNode* node = X3DByType_avl::find(&m_nodesByTypeHeader, nodeType, X3DNode_compareByType());
	if (node == X3DByType_avl::end_node(&m_nodesByTypeHeader))
	{
		return nullptr;
	}
	return node;
}

vector<X3DNode*> X3DScene::NodesByTypeSnapshot(StringIn nodeTypeName)
{
	CriticalSectionLock lock(m_nodesByTypeHeaderCS);

	vector<X3DNode*> v;
	X3DNode* node = X3DByType_avl::find(&m_nodesByTypeHeader, nodeTypeName, X3DNode_compareByType());
	if (node != X3DByType_avl::end_node(&m_nodesByTypeHeader))
	{
		do
		{
			v.push_back(node);
			node = X3DByType_avl::next_node(node);
		}
		while (node != X3DByType_avl::end_node(&m_nodesByTypeHeader) &&
			node->getTypeName() == nodeTypeName);
	}
	return v;
}

WorldInfo* X3DScene::get_WorldInfoNode()
{
	X3DNode* node = NodeByType("WorldInfo");
	return static_cast<WorldInfo*>(node);
}

String X3DScene::get_Title()
{
	WorldInfo* worldInfo = get_WorldInfoNode();
	if (worldInfo)
	{
		return worldInfo->getTitleField()->getValue();
	}
	return nullptr;
}

X3DEXT SceneVisual3D* View(X3DScene* scene)
{
	if (scene->get_Viewpoint() == nullptr)
	{
		Console::get_Out() << "X3DScene doesn't have a Viewpoint node" << endl;
	}

	SceneVisual3D* view = new SceneVisual3D(scene);

	Gui::Window* win = new Gui::Window(view, gm::SizeF(600, 500));
	win->Show();

	return view;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

class TreeViewFieldController : public Object, public Gui::ITreeViewController
{
public:

	CTOR TreeViewFieldController(X3DNode* node)
	{
		m_fontSize = 17;
	}

	virtual float GetItemHeight(Gui::TreeItem item) override;
	virtual int GetItemState(Gui::TreeItem item) override;
	virtual void RenderItem(Gui::TreeItem item, Gui::ManagedRenderContext renderContext, gm::RectF) override;
	virtual int ClickItem(Gui::TreeItem item, gm::RectF, gm::PointF clickpos) override;
	virtual uint GetChildrenCount(Gui::TreeItem item) override;
	virtual Gui::TreeItem GetChild(Gui::TreeItem item, uint index) override;

	Gui::TextFormat* m_textFormat;
	String m_fontFamily;
	float m_fontSize;

	Gui::Brush* m_textBrush;
	Gui::Brush* m_selectedBgBrush;
	Gui::Brush* m_selectedTextBrush;

	X3DNodeSelection* m_selection;
};

class TreeViewController : public Object, public Gui::ITreeViewController
{
public:

	CTOR TreeViewController(X3DScene* scene)
	{
		m_fontSize = 17;
	}

	virtual float GetItemHeight(Gui::TreeItem item) override;
	virtual int GetItemState(Gui::TreeItem item) override;
	virtual void RenderItem(Gui::TreeItem item, Gui::ManagedRenderContext renderContext, gm::RectF) override;
	virtual int ClickItem(Gui::TreeItem item, gm::RectF, gm::PointF clickpos) override;
	virtual uint GetChildrenCount(Gui::TreeItem item) override;
	virtual Gui::TreeItem GetChild(Gui::TreeItem item, uint index) override;
	virtual Gui::TreeItem GetRoot() override;

	Gui::TextFormat* m_textFormat;
	String m_fontFamily;
	float m_fontSize;

	Gui::Brush* m_textBrush;
	Gui::Brush* m_selectedBgBrush;
	Gui::Brush* m_selectedTextBrush;

	X3DNodeSelection* m_selection;
};

float TreeViewController::GetItemHeight(Gui::TreeItem item)
{
	return m_fontSize;
}

void TreeViewController::RenderItem(Gui::TreeItem item, Gui::ManagedRenderContext renderContext, gm::RectF rect)
{
	if (m_textFormat == nullptr)
	{
		m_textFormat = new Gui::TextFormat(S(L"Arial"), m_fontSize);
		m_textBrush = new Gui::SolidColorBrush(0,0,0,1);
		m_selectedBgBrush = new Gui::SolidColorBrush(0.3f, 0.3f, 0.8f, 1.0f);
		m_selectedTextBrush = new Gui::SolidColorBrush(1.0f, 1.0f, 1.0f, 1.0f);
	}

	X3DNode* node = dynamic_cast<X3DNode*>(item.data0);
	ASSERT(node);

	if (GetItemState(item))
	{
		renderContext.FillRectangle(rect, m_selectedBgBrush);
		renderContext.OutputText(node->getTypeName(), m_selectedTextBrush, m_textFormat, rect);
	}
	else
	{
		renderContext.OutputText(node->getTypeName(), m_textBrush, m_textFormat, rect);
	}
}

int TreeViewController::ClickItem(Gui::TreeItem item, gm::RectF, gm::PointF)
{
	X3DNode* node = dynamic_cast<X3DNode*>(item.data0);
	ASSERT(node);

	OleDataObject* dataObject = new OleDataObject;
	dataObject->AddRef();

	OleDropSource* dropSource = new OleDropSource;
	dropSource->AddRef();

	DWORD dropEffect = 0;
	if (DoDragDrop(dataObject, dropSource, DROPEFFECT_COPY | DROPEFFECT_MOVE, &dropEffect) == DRAGDROP_S_DROP)
	{
	}

	dataObject->Release();
	dropSource->Release();

	for (auto it = m_selection->m_items.begin(); it != m_selection->m_items.end(); ++it)
	{
		it->first->m_selected = false;
	}

	m_selection->m_items.clear();
	m_selection->m_items[node] = true;
	node->m_selected = true;
	m_selection->SelectionChanged(m_selection);

	return 1;
}

Gui::TreeItem TreeViewController::GetRoot()
{
	return nullptr;
}

uint TreeViewController::GetChildrenCount(Gui::TreeItem item)
{
	if (X3DGroupingNode* node = dynamic_cast<X3DGroupingNode*>(item.data0))
	{
		return node->getChildrenField()->get_size();
	}
	else if (Layer* node = dynamic_cast<Layer*>(item.data0))
	{
		return node->getChildrenField()->get_size();
	}

	return 0;
}

Gui::TreeItem TreeViewController::GetChild(Gui::TreeItem item, uint index)
{
	if (X3DGroupingNode* node = dynamic_cast<X3DGroupingNode*>(item.data0))
	{
		return Gui::TreeItem(item.controller, node->getChildrenField()->get1Value(index));
	}
	else if (Layer* node = dynamic_cast<Layer*>(item.data0))
	{
		return Gui::TreeItem(item.controller, node->getChildrenField()->get1Value(index));
	}

	ASSERT(0);
}

int TreeViewController::GetItemState(Gui::TreeItem item)
{
	X3DNode* node = dynamic_cast<X3DNode*>(item.data0);
	ASSERT(node);

	return m_selection->m_items.find(node) != m_selection->m_items.end();
}

float TreeViewFieldController::GetItemHeight(Gui::TreeItem item)
{
	return m_fontSize;
}

void TreeViewFieldController::RenderItem(Gui::TreeItem item, Gui::ManagedRenderContext renderContext, gm::RectF rect)
{
	if (m_textFormat == nullptr)
	{
		m_textFormat = new Gui::TextFormat(S(L"Arial"), m_fontSize);
		m_textBrush = new Gui::SolidColorBrush(0,0,0,1);
		m_selectedBgBrush = new Gui::SolidColorBrush(0.3f, 0.3f, 0.8f, 1.0f);
		m_selectedTextBrush = new Gui::SolidColorBrush(1.0f, 1.0f, 1.0f, 1.0f);
	}

	X3DField* field = dynamic_cast<X3DField*>(item.data0);
	ASSERT(field);

	if (GetItemState(item))
	{
		renderContext.FillRectangle(rect, m_selectedBgBrush);
		renderContext.OutputText(field->getFieldName(), m_selectedTextBrush, m_textFormat, rect);
	}
	else
	{
		renderContext.OutputText(field->getFieldName(), m_textBrush, m_textFormat, rect);
	}
}

int TreeViewFieldController::ClickItem(Gui::TreeItem item, gm::RectF, gm::PointF)
{
	X3DField* node = dynamic_cast<X3DField*>(item.data0);
	ASSERT(node);

	/*
	std::map<X3DNode*,bool>::iterator it = m_selection->m_items.begin();
	while (it != m_selection->m_items.end())
	{
		it->first->m_selected = false;
		++it;
	}

	m_selection->m_items.clear();
	m_selection->m_items[node] = true;
	node->m_selected = true;
	m_selection->SelectionChanged(m_selection);
	*/

	return 1;
}

uint TreeViewFieldController::GetChildrenCount(Gui::TreeItem item)
{
	SFNode* node = dynamic_cast<SFNode*>(item.data0);
	if (node)
	{
		return 1;//node->get_children()->get_size();
	}

	return 0;
}

Gui::TreeItem TreeViewFieldController::GetChild(Gui::TreeItem item, uint index)
{
	SFNode* node = dynamic_cast<SFNode*>(item.data0);
	ASSERT(node);
	if (index != 0)
	{
		raise(ArgumentOutOfRangeException());
	}

	ASSERT(0);
	throw new Exception();
	//return Gui::TreeItem(new TreeViewController(nullptr), node->getValue());
}

int TreeViewFieldController::GetItemState(Gui::TreeItem item)
{
	X3DField* field = dynamic_cast<X3DField*>(item.data0);
	ASSERT(field);

	return 0;
	//return m_selection->m_items.find(node) != m_selection->m_items.end();
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

X3DEXT TextDocument* asvrml(X3DScene* scene)
{
	TextDocument* td = new TextDocument;
	td->IncRef();
	AddView(scene, td);
	td->m_Mimetype = "model/x3d+vrml";
	scene->WriteVRML(*td);
	return td;
}

void xmlNodes(IXmlWriter* xmlwriter, MFNode* mfode);

X3DEXT Object* asxml(X3DScene* scene)
{
	XmlData::XmlWriter* xmlwriter = new XmlData::XmlWriter();

	xmlwriter->BeginDocument();

	//	td->m_Mimetype = "model/x3d+vrml";

	xmlwriter->BeginElement(L"X3D");
	xmlwriter->Attribute(L"version", scene->getSpecificationVersion());
	xmlwriter->Attribute(L"profile", L"Immersive");

	xmlwriter->BeginElement(L"head");

	for (auto it = scene->m_metadata.begin(); it != scene->m_metadata.end(); ++it)
	{
		xmlwriter->BeginElement(L"meta");
		xmlwriter->Attribute(L"name", it->first);
		xmlwriter->Attribute(L"content", it->second);
		xmlwriter->EndElement();
	}

	xmlwriter->EndElement();	// head

	xmlwriter->BeginElement(L"X3DScene");
	xmlNodes(xmlwriter, scene->getRootNodes());
	xmlwriter->EndElement();

	xmlwriter->EndElement();	// X3D

	AddView(scene, xmlwriter->m_document);

	return xmlwriter->m_document;
}

X3DEXT Gui::TreeView* TreeOf(X3DScene* scene)
{
	TreeViewController* controller = new TreeViewController(scene);

	Gui::TreeView* treeView = new Gui::TreeView(controller);
	treeView->m_item = Gui::TreeItem(controller, scene->m_root);

	controller->m_selection = scene->m_defaultView->get_Selection();

	return treeView;
}

X3DEXT void Show(Gui::TreeView* view)
{
	Gui::Window* win = new Gui::Window(view);
	win->set_Width(600);
	win->set_Height(500);

	win->Show();
}

X3DEXT vector<X3DNode*> filter(const vector<X3DNode*>& v, bool (*pred)(X3DNode* node))
{
	vector<X3DNode*> r;
	for (auto it = v.cbegin(); it != v.cend(); ++it)
	{
		if (pred(*it)) r.push_back(*it);
	}

	return r;
}

X3DEXT void foreach(const vector<X3DNode*>& v, void (*func)(X3DNode* node))
{
	for (auto it = v.cbegin(); it != v.cend(); ++it)
	{
		func(*it);
	}
}

}	// x3d
}	// System
