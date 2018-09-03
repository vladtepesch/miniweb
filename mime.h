/*********************************************************************************************//**
 *  \file
 *
 *  
 * contains some functions for mimetype handling 
 *
 *//*********************************************************************************************/

#ifndef MIME_h__0708305
#define MIME_h__0708305


#ifdef __cplusplus
extern "C" {
#endif




/**
 * Internal enumeration of content types.
 * Beside the some predefined constants there is no special or somehow fixed numbering of different types.
 */
typedef int HttpFileType;

// some predefined content types 
#define   MIMETYPE_UNKNOWN   0
#define   MIMETYPE_HTML      1
#define   MIMETYPE_OCTET     2
#define   MIMETYPE_JS        3
#define   MIMETYPE_TEXT      4
#define   MIMETYPE_XML       5

/** 
 * sets up the some internals and have to be called before any other requests.
 */
void Mime_init();


/** returns content type for the given extension */
HttpFileType Mime_getTypeFromExt(const char* i_fileExt);

/** 
 * returns a mime type string (e.g application/octet-stream) for the intern type 
 *  unknown will be handled like application/octet-stream
 */
const char*  Mime_getMimeStringFromType(HttpFileType i_type);

/**
 * returns the associated mime-type for a file-extension.
 */
static const char*  Mime_getMimeStringFromExt(const char* i_fileExt) {
  return Mime_getMimeStringFromType(Mime_getTypeFromExt(i_fileExt));
}





#ifdef __cplusplus
}
#endif

#endif /* MIME_h__0708305 */

