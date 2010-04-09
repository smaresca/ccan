#include <tools/ccanlint/ccanlint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <ccan/str/str.h>
#include <ccan/talloc/talloc.h>
#include <ccan/noerr/noerr.h>

static void *check_has_main_header(struct manifest *m, unsigned int *timeleft)
{
	struct ccan_file *f;

	list_for_each(&m->h_files, f, list) {
		if (strstarts(f->name, m->basename)
		    && strlen(f->name) == strlen(m->basename) + 2)
			return NULL;
	}
	return m;
}

static const char *describe_has_main_header(struct manifest *m,
					    void *check_result)
{
	return talloc_asprintf(m,
	"You have no %s/%s.h header file.\n\n"
	"CCAN modules have a name, the same as the directory name.  They're\n"
	"expected to have an interface in the header of the same name.\n",
			       m->basename, m->basename);
}

struct ccanlint has_main_header = {
	.key = "has-main-header",
	.name = "Module has main header file",
	.check = check_has_main_header,
	.describe = describe_has_main_header,
};

REGISTER_TEST(has_main_header, NULL);
