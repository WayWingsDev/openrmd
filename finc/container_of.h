#ifndef _CONTAINER_OF_H_
#define _CONTAINER_OF_H_

#ifndef offsetof
#define offsetof(type, member) \
	(size_t)&(((type *)0)->member)
#endif

#ifndef container_of
#define container_of(ptr, type, member)  \
	({\
		const typeof(((type *)0)->member) * __mptr = (ptr);\
		(type *)((char *)__mptr - offsetof(type, member)); \
	})
#endif

#endif	/* _CONTAINER_OF_H_ */
