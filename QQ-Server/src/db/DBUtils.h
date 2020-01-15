#ifndef QQ_SERVER_DBUTILS_H
#define QQ_SERVER_DBUTILS_H

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset_metadata.h>

#include <iostream>

class DBUtils
{
private:
    static sql::Driver* get_driver()
    {
        /* Create a connection */
        static sql::Driver* driver = get_driver_instance();
        return driver;
    }

    static sql::Connection* get_connection()
    {
        sql::Driver* driver = get_driver();
        sql::Connection* conn = driver->connect("tcp://192.168.1.123:3306", "root", "abc123_");
        conn->setSchema("qq");

        return conn;
    }

public:
    static string get_pwd_by_name(string & name)
    {
        try {
            sql::Connection* conn;
            sql::PreparedStatement* prep_stmt;
            sql::ResultSet* res;

            /* Create a connection */
            conn = get_connection();
            prep_stmt = conn->prepareStatement("select username, password from user where nickname = ?");
            prep_stmt->setString(1, name);
            res = prep_stmt->executeQuery();

            string password;
            while (res->next()) {
                password = res->getString("password");
            }

            delete res;
            delete prep_stmt;
            delete conn;

            return password;

        }
        catch (sql::SQLException & e) {
            cout << "# ERR: " << e.what();
        }
    }
};

#endif