/*********************************************************************************************//**
 *  \file
 *
 *
 *//*********************************************************************************************/

#include "mime.h"

#include <cstring>
#include <map>


// 
// create this file from apache mime.types
//   http://svn.apache.org/viewvc/httpd/httpd/branches/2.2.x/docs/conf/mime.types?view=co
// and post process with (under windows - great hassle with quotes so hide them in variable):
// perl -nle " if(! /^#/) { $qte = chr(34);$_ =~ s/$qte/'/mg; s/\s+/\\0/g; print  $qte .  $_ . '\0\0'. $qte;}" mime.types > mime.types.c.txt
// 
// - each entry consists of multiple strings delimited by \0 
//   - first string is the type
//   - then n file extensions each delimited by \0
//   - an additional zero to mark the end of extension lists
// - an additional \0 to mark the end of mime type lists.
static const char s_mimeData[] = 
#include "mime.types.c.txt"
 
"\0"
;


#define MIME_TYPES_MAX 4096


static const char*   s_mimeTypes[MIME_TYPES_MAX] = {
  "application/octet-stream",
  "text/html",
  "application/octet-stream",
  "application/javascript", 
  "text/plain",
  "text/xml",
};
static size_t s_mimeTypesSize = 6;

static size_t findInMimeTypes(const char* i_str) {
  
  for (size_t i = 0; i < s_mimeTypesSize; ++i) {
    if ( strcmp(s_mimeTypes[i], i_str) == 0) {
      return i;
    }
  }
  return s_mimeTypesSize;
}


struct cmp_str
{
  bool operator()(const char* const a, const char* const b)const
  {
    return strcmp(a, b) < 0;
  }
};

static std::map<const char*, int, cmp_str> s_extToMT;


void Mime_init()
{
  const char* p = s_mimeData;
  while (*p) {
    const char* mtype = p;
    p += strlen(p)+1;

    size_t ind = findInMimeTypes( mtype);
    if (ind == s_mimeTypesSize) {
      if (s_mimeTypesSize < MIME_TYPES_MAX) {
        ind = s_mimeTypesSize;
        s_mimeTypes[s_mimeTypesSize] = mtype;
        s_mimeTypesSize++;
      }
    }

    while (*p) {
      const char* ext = p;
      s_extToMT[p] = ind;
      p += strlen(p) + 1;
    }

    p += strlen(p) + 1;

  }

  //std::string line;
  //while (std::getline(sstr, line)) {
  //  if ( line[0] != '#') {
  //    std::vector<std::string> elems;
  //    split4(line, elems, " \t");
  //    if (elems.size() > 1) {
  //      int ind = 0;
  //      auto it = std::find(s_mimeTypes, s_mimeTypes+ s_mimeTypesSize, elems[0]);
  //      if (it != s_mimeTypes.end()) {
  //        ind = std::distance(s_mimeTypes.begin(), it);
  //      } else {
  //        ind = s_mimeTypes.size();
  //        s_mimeTypes.push_back(elems[0]);
  //      }
  //      for (size_t i = 1; i < elems.size(); ++i) {
  //        s_extToMT[elems[i]] = ind;
  //      }
  //    }
  //
  //  }
  //
  //}

}

HttpFileType Mime_getTypeFromExt(const char* i_fileExt)
{
  if (i_fileExt) {
    const auto& exttoMT = s_extToMT;
    if (i_fileExt[0] == '.') {
      i_fileExt++;
    }
    auto it = exttoMT.find(i_fileExt);
    if (it != exttoMT.end()) {
      return it->second;
    }
  }
  return MIMETYPE_UNKNOWN;

}

const char* Mime_getMimeStringFromType(HttpFileType i_type)
{
  if (i_type >= 0 && (size_t)i_type < s_mimeTypesSize) {
    return s_mimeTypes[i_type];
  }
  return s_mimeTypes[0];
}
