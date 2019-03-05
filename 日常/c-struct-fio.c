#include <stdio.h>
#include <memory.h>
#include <limits.h>

struct row
{
	int id;
	int num;
	long long s;
};


int main_write()
{
	FILE *f = fopen("t.db", "wb");
	FILE *index = fopen("index.txt", "w");

	for (int i = 0; i < 1000; ++i)
	{
		row r;
		r.id = i;
		r.num = i + 1;
		r.s = r.num * r.num;

		fprintf(index, "%d -> %ld\n", r.id, ftell(f));

		int ret = fwrite(&r, sizeof(row), 1, f);
		if (ret != 1)
			fprintf(stderr, "write failed : id : %d", r.id);
	}

	fclose(index);
	fclose(f);

	return 0;
}

int main_read()
{
	FILE *f = fopen("t.db", "rb");
	row r;
	memset(&r, 0, sizeof(row));

	int ret = 0;
	ret = fseek(f, 15984l, SEEK_SET);
	printf("fseek -> %d\n", ret);
	ret = fread(&r, sizeof(row), 1, f);
	if (ret != 1)
	{
		printf("ferror -> %d\n", ferror(f));
		printf("feof -> %d\n", feof(f));
	}

	printf("r.s -> %lld\n", r.s);

	fclose(f);
	return 0;
}

int main()
{
	printf("sizeof(row): %d\n", sizeof(row));
	return main_read();
}