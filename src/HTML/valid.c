/*
 * valid.c : part of the code use to do the DTD handling and the validity
 *           checking
 *
 * See Copyright for the status of this software.
 *
 * daniel@veillard.com
 */

#include "libxml.h"

#include <string.h>

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include <libxml/xmlmemory.h>
#include <libxml/hash.h>
#include <libxml/valid.h>
#include <libxml/parser.h>
#include <libxml/parserInternals.h>
#include <libxml/xmlerror.h>
#include <libxml/list.h>
#include <libxml/globals.h>

/**
 * xmlGetID:
 * @doc:  pointer to the document
 * @ID:  the ID value
 *
 * Search the attribute declaring the given ID
 *
 * Returns NULL if not found, otherwise the xmlAttrPtr defining the ID
 */
xmlAttrPtr 
xmlGetID(xmlDocPtr doc, const xmlChar *ID) {
    xmlIDTablePtr table;
    xmlIDPtr id;

    if (doc == NULL) {
     ;//   xmlGenericError(xmlGenericErrorContext, "xmlGetID: doc == NULL\n");
	return(NULL);
    }

    if (ID == NULL) {
        ;//xmlGenericError(xmlGenericErrorContext, "xmlGetID: ID == NULL\n");
	return(NULL);
    }

    table = (xmlIDTablePtr) doc->ids;
    if (table == NULL) 
        return(NULL);

    id = xmlHashLookup(table, ID);
    if (id == NULL)
	return(NULL);
    return(id->attr);
}
