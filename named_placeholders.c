#include "sqlite3.h"
#include <stdio.h>
#include <string.h>

#define MaxSqlStatementLength 1024

char LastSqlStatment[MaxSqlStatementLength];

char *GetLastSql()
{
	return LastSqlStatment;
}

static int tracer(unsigned NameMe1, void *NameMe2, void *p, void *NameMe3)
{
    sqlite3_stmt *stmt = (sqlite3_stmt*)p;
    char *sql = sqlite3_expanded_sql(stmt);
	
	if (strlen(sql) < MaxSqlStatementLength -1 )
	{
		strcpy(LastSqlStatment, sql);
	}
	else
	{
		LastSqlStatment[0] = '\0';
	}
	
//    printf("tracer - %s\n", sql);
    sqlite3_free(sql);
    return 0;
}

int main(void)
{
    sqlite3 *db;
    char *err_msg = 0;
    sqlite3_stmt *res;
	
	LastSqlStatment[0] = '\0';
	
	printf("Hello world\n");

    /* open our database */	
	int rc = sqlite3_open("CprojCallingSQLite.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return 1;
    }
	
	/* Prepare for the trace */
	sqlite3_trace_v2(db, SQLITE_TRACE_STMT, tracer, NULL);
	
	/* our query we want to do with replacable arguments */
    char *sql = "SELECT Id, Name FROM Cars WHERE Id = @id";
    
	/* get ready for using our sql query to query the database */
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    
    if (rc == SQLITE_OK) 
	{
	    /* Now do the argument binding to get ready for the query */		
        int idx = sqlite3_bind_parameter_index(res, "@id");
        int value = 4;
        sqlite3_bind_int(res, idx, value);
		
		/* Now DO our sql query */
        int step = sqlite3_step(res);
		
		/* print the results */
		if (step == SQLITE_ROW)
		{
			char *ExecutedSql = GetLastSql();
			if (ExecutedSql)
			{
				printf("Executed sql: %s\n", ExecutedSql);
			}
			
	        printf("%s: ", sqlite3_column_text(res, 0));
            printf("%s\n", sqlite3_column_text(res, 1));	
		}
    }
	else 
	{
		fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

	// wrap up and clean up.
	sqlite3_finalize(res);
    sqlite3_close(db);

	printf("Bye\n");

	return 0;
}

