#pragma once

template <typename T>
class writer
{
public:
	writer() = default;
	~writer() = default;

	void write(const char* str) const
	{
		static_cast<const T*>(this)->write_impl(str);
	}
};

class file_writer : public writer<file_writer>
{
public:
	static FILE* mfile;

	void write_impl(const char* str) const
	{
		fprintf(mfile, "%s\n", str);
	}
};
FILE* file_writer::mfile = nullptr;

class file_writer2 : public writer<file_writer2>
{
	FILE* mfile;
public:
	file_writer2(FILE* m)
	{
		mfile = m;
	}
	~file_writer2()
	{
		fclose(mfile);
	}
	void write_impl(const char* str) const
	{
		fprintf(mfile, "%s\n", str);
	}
};

class console_writer : public writer<console_writer>
{
public:
	console_writer() = default;
	~console_writer() = default;
	void write_impl(const char* str) const
	{
		printf("%s\n", str);
	}
};