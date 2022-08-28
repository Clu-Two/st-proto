#pragma once

class master_db
{
public:
	enum class DB_Type
	{
		FILE,
		SQLITE
	};
	
	bool Load_sql3(const char* sz_filename, master_db &MASTER_DB);
	bool Load_DB(const char* sz_filename, DB_Type db_type /*= DB_Type::FILE*/);
	bool Make_sql3(const char* sz_filename);

};


extern const char* sqlstatement(const char* format, ...);