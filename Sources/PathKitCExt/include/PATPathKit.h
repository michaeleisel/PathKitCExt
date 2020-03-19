
#include <stddef.h>

#ifdef __cplusplus
export "C" {
#endif

void PATFreePathComponents(const char **components, void *temp);
const char **PATPathComponents(const char *path, size_t *count, void **temp);

#ifdef __cplusplus
}
#endif
