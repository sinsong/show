size_t strlen_gbk(const char* str)
{
	size_t sz = 0;
	unsigned char key = 1U << 7;
	while (*str != '\0')
	{
		if ((*str & key) != 0)
		{
			++str; // 中文两字节，跳一下
		}
		++sz;
		++str;
	}
	return sz;
}