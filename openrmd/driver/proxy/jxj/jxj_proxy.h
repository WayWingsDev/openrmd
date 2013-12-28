#ifndef _JXJ_PROXY_H_
#define _JXJ_PROXY_H_

#if defined(_WIN32_)
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

DLLEXPORT struct dp_t *dp_get();

#endif /* _JXJ_PROXY_H_ */