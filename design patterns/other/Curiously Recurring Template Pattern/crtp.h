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