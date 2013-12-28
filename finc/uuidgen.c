#include "syshdr.h"
#include "uuidgen.h"

#ifdef _WIN32_
#include <objbase.h>
#else
#include <uuid/uuid.h>
#endif

int uuidgen(char *uuid)
{
#ifdef _WIN32_
	GUID guid;

	if (CoCreateGuid(&guid) != S_OK)
		return -1;
	sprintf(uuid, "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
			guid.Data1,
			guid.Data2,
			guid.Data3,
			guid.Data4[0], guid.Data4[1],
			guid.Data4[2], guid.Data4[3], guid.Data4[4],
			guid.Data4[5], guid.Data4[6], guid.Data4[7]);
#else
	uuid_t id;

	uuid_generate(id);
	uuid_unparse(id, uuid);
#endif

	return 0;
}
