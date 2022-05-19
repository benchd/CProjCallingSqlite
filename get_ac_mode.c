#include <sqlite3.h>
#include <stdio.h>

int main() {
    
    sqlite3 *db;
    
    int rc = sqlite3_open("test.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", 
                sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return 1;
    }    
    
    printf("Autocommit: %d\n", sqlite3_get_autocommit(db));
    
    sqlite3_close(db);
    
    return 0;
}