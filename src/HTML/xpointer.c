#include "libxml.h"

/*
 * TODO: better handling of error cases, the full expression should
 *       be parsed beforehand instead of a progressive evaluation
 * TODO: Access into entities references are not supported now ...
 *       need a start to be able to pop out of entities refs since
 *       parent is the endity declaration, not the ref.
 */

#include <string.h>
#include <libxml/xpointer.h>
#include <libxml/xmlmemory.h>
#include <libxml/parserInternals.h>
#include <libxml/uri.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <libxml/xmlerror.h>
#include <libxml/globals.h>


/**
 * xmlXPtrLocationSetMerge:
 * @val1:  the first LocationSet
 * @val2:  the second LocationSet
 *
 * Merges two rangesets, all ranges from @val2 are added to @val1
 *
 * Returns val1 once extended or NULL in case of error.
 */
xmlLocationSetPtr
xmlXPtrLocationSetMerge(xmlLocationSetPtr val1, xmlLocationSetPtr val2) {
#if 0
    int i;

    if (val1 == NULL) return(NULL);
    if (val2 == NULL) return(val1);

    /*
     * !!!!! this can be optimized a lot, knowing that both
     *       val1 and val2 already have unicity of their values.
     */

    for (i = 0;i < val2->locNr;i++)
        xmlXPtrLocationSetAdd(val1, val2->locTab[i]);
#endif
    return(val1);
}
