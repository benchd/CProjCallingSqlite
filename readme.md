echo on
path
rem stop and install gcc so it can find it in the path.
echo for Windows, this url works: https://dev.to/gamegods3/how-to-install-gcc-in-windows-10-the-easier-way-422j
echo see if \mingw\bni is in path, if not
echo pause.
call .\setPath.bat
echo pause
echo get the version of sqlite3 installed
call .\Doit.bat
  version.exe
echo pause
echo get the version of sqlite3 installed another way
call .\Doit2.bat
 version2.exe
echo pause
echo Create our database and insert sample data into it.
call .\Doit3.bat
insert_data.exe
echo pause
echo query our database with an named parameter. set SQLite_TRACE_v2. to grab the sql query with arguments already replaced.
Echo This is the one with the call to SQLite_TRACE_V2 enabled, and printing results.
call .\Doit4.bat
named_placeholders.exe
Exit
call .\Doit5.bat
select_all.exe
call .\Doit6.bat
list_tables.exe
echo This one has no such table Friend.
call .\Doit7.bat
autocommit.exe
call .\Doit8.bat
column_names.exe
call .\Doit9.bat
list_tables.exe
echo This one has cannot open image file.
call .\Doit10.bat
insert_image.exe
call .\Doit11.bat
last_row_id.exe
call .\Doit12.bat
parameterized.exe
echo This one has no such table Images.
call .\Doit13.bat
read_image.exe
echo this one has no such table Friend.
call .\Doit14.bat
transaction.exe


