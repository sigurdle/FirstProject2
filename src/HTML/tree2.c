#include "libxml.h"

#include <string.h> /* for memset() only ! */

#ifdef HAVE_CTYPE_H
#include <ctype.h>
#endif
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef HAVE_ZLIB_H
#include <zlib.h>
#endif

#include <libxml/xmlmemory.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/uri.h>
#include <libxml/entities.h>
#include <libxml/valid.h>
#include <libxml/xmlerror.h>
#include <libxml/parserInternals.h>
#include <libxml/globals.h>


/**
 * xmlBufferFree:
 * @buf:  the buffer to free
 *
 * Frees an XML buffer.
 */
void
xmlBufferFree(xmlBufferPtr buf) {
    if (buf == NULL) {
#ifdef DEBUG_BUFFER
        xmlGenericError(xmlGenericErrorContext,
		"xmlBufferFree: buf == NULL\n");
#endif
	return;
    }
    if (buf->content != NULL) {
        xmlFree(buf->content);
    }
    xmlFree(buf);
}

/**
 * xmlBufferAdd:
 * @buf:  the buffer to dump
 * @str:  the xmlChar string
 * @len:  the number of xmlChar to add
 *
 * Add a string range to an XML buffer. if len == -1, the length of
 * str is recomputed.
 */
void
xmlBufferAdd(xmlBufferPtr buf, const xmlChar *str, int len) {
    unsigned int needSize;

    if (str == NULL) {
#ifdef DEBUG_BUFFER
        xmlGenericError(xmlGenericErrorContext,
		"xmlBufferAdd: str == NULL\n");
#endif
	return;
    }
    if (len < -1) {
#ifdef DEBUG_BUFFER
        xmlGenericError(xmlGenericErrorContext,
		"xmlBufferAdd: len < 0\n");
#endif
	return;
    }
    if (len == 0) return;

    if (len < 0)
        len = xmlStrlen(str);

    if (len <= 0) return;

    needSize = buf->use + len + 2;
    if (needSize > buf->size){
        if (!xmlBufferResize(buf, needSize)){
            xmlGenericError(xmlGenericErrorContext,
		    "xmlBufferAdd : out of memory!\n");
            return;
        }
    }

    memmove(&buf->content[buf->use], str, len*sizeof(xmlChar));
    buf->use += len;
    buf->content[buf->use] = 0;
}

/**
 * xmlBufferAddHead:
 * @buf:  the buffer
 * @str:  the xmlChar string
 * @len:  the number of xmlChar to add
 *
 * Add a string range to the beginning of an XML buffer.
 * if len == -1, the length of @str is recomputed.
 */
void
xmlBufferAddHead(xmlBufferPtr buf, const xmlChar *str, int len) {
    unsigned int needSize;

    if (str == NULL) {
#ifdef DEBUG_BUFFER
        xmlGenericError(xmlGenericErrorContext,
		"xmlBufferAdd: str == NULL\n");
#endif
	return;
    }
    if (len < -1) {
#ifdef DEBUG_BUFFER
        xmlGenericError(xmlGenericErrorContext,
		"xmlBufferAdd: len < 0\n");
#endif
	return;
    }
    if (len == 0) return;

    if (len < 0)
        len = xmlStrlen(str);

    if (len <= 0) return;

    needSize = buf->use + len + 2;
    if (needSize > buf->size){
        if (!xmlBufferResize(buf, needSize)){
            xmlGenericError(xmlGenericErrorContext,
		    "xmlBufferAddHead : out of memory!\n");
            return;
        }
    }

    memmove(&buf->content[len], &buf->content[0], buf->use * sizeof(xmlChar));
    memmove(&buf->content[0], str, len * sizeof(xmlChar));
    buf->use += len;
    buf->content[buf->use] = 0;
}

/**
 * xmlBufferResize:
 * @buf:  the buffer to resize
 * @size:  the desired size
 *
 * Resize a buffer to accomodate minimum size of @size.
 *
 * Returns  0 in case of problems, 1 otherwise
 */
int
xmlBufferResize(xmlBufferPtr buf, unsigned int size)
{
    unsigned int newSize;
    xmlChar* rebuf = NULL;

    /*take care of empty case*/
    newSize = (buf->size ? buf->size*2 : size);

    /* Don't resize if we don't have to */
    if (size < buf->size)
        return 1;

    /* figure out new size */
    switch (buf->alloc){
    case XML_BUFFER_ALLOC_DOUBLEIT:
        while (size > newSize) newSize *= 2;
        break;
    case XML_BUFFER_ALLOC_EXACT:
        newSize = size+10;
        break;
    default:
        newSize = size+10;
        break;
    }

    if (buf->content == NULL)
	rebuf = (xmlChar *) xmlMalloc(newSize * sizeof(xmlChar));
    else
	rebuf = (xmlChar *) xmlRealloc(buf->content, 
				       newSize * sizeof(xmlChar));
    if (rebuf == NULL) {
        xmlGenericError(xmlGenericErrorContext,
		"xmlBufferAdd : out of memory!\n");
        return 0;
    }
    buf->content = rebuf;
    buf->size = newSize;

    return 1;
}
