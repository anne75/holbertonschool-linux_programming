#include "readelf_header.h"

typedef uint64_t bfd_size_type;

void * get_data(void * var, FILE * file, unsigned long offset,
			bfd_size_type size,
			bfd_size_type nmemb, const char * reason)
{
	void * mvar;
	bfd_size_type amt = size * nmemb;
	if (size == 0 || nmemb == 0)
		return NULL;
	/* If the size_t type is smaller than the bfd_size_type, eg because
	   you are building a 32-bit tool on a 64-bit host, then make sure
	   that when the sizes are cast to (size_t) no information is lost.  */
	if (sizeof(size_t) < sizeof(bfd_size_type)
	    && (   (bfd_size_type) ((size_t) size) != size
		   || (bfd_size_type) ((size_t) nmemb) != nmemb))
	{
		if (reason)
			fprintf(stderr,
				"Size truncation prevents reading 0x%llx elements of size 0x%llx for %s\n",
				(unsigned long long) nmemb, (unsigned long long) size, reason);
		return (NULL);
	}
	/* Check for size overflow.  */
	if (amt < nmemb)
	{
		if (reason)
			fprintf(stderr, "Size overflow prevents reading 0x%llx elements of size 0x%llx for %s\n",
			       (unsigned long long) nmemb, (unsigned long long) size, reason);
		return (NULL);
	}
	/* Be kind to memory chekers (eg valgrind, address sanitizer) by not
	   attempting to allocate memory when the read is bound to fail.  */
	if (amt > current_file_size
	    || offset + archive_file_offset + amt > current_file_size)
	{
		if (reason)
			fprintf(stderr, "Reading 0x%llx bytes extends past end of file for %s\n",
			       (unsigned long long) amt, reason);
		return (NULL);
	}
	if (fseek(file, archive_file_offset + offset, SEEK_SET))
	{
		if (reason)
			fprintf(stderr, "Unable to seek to 0x%lx for %s\n",
				(unsigned long) archive_file_offset + offset, reason);
		return (NULL);
	}
	mvar = var;
	if (mvar == NULL)
	{
		/* Check for overflow.  */
		if (nmemb < (~(bfd_size_type) 0 - 1) / size)
			/* + 1 so that we can '\0' terminate invalid string table sections.  */
			mvar = malloc((size_t) amt + 1);
		if (mvar == NULL)
		{
			if (reason)
				fprintf(stderr, "Out of memory allocating 0x%llx bytes for %s\n",
				       (unsigned long long) amt, reason);
			return (NULL);
		}
		((char *) mvar)[amt] = '\0';
	}
	if (fread(mvar, (size_t) size, (size_t) nmemb, file) != nmemb)
	{
		if (reason)
			fprintf(stderr, "Unable to read in 0x%llx bytes of %s\n",
				(unsigned long long) amt, reason);
		if (mvar != var)
			free(mvar);
		return (NULL);
	}
	return (mvar);
}
