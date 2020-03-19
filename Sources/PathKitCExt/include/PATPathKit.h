
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

const char **PATContentsAt(const char *path, size_t *count, void **temp);
void PATFreePathComponents(const char **components, void *temp);
const char **PATPathComponents(const char *path, size_t *count, void **temp);

#ifdef __cplusplus
}
#endif
