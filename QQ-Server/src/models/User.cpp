#include "User.h"
#include "DBUtils.h"

using namespace std;

string& User::get_pwd_by_username(string& pwd, string& name)
{
    try {
        sql::Connection* conn;
        sql::PreparedStatement* prep_stmt;
        sql::ResultSet* res;

        /* Create a connection */
        conn = DBUtils::get_connection();
        prep_stmt = conn->prepareStatement("select username, password from User where nickname = ?");
        prep_stmt->setString(1, name);
        res = prep_stmt->executeQuery();

        while (res->next()) {
            pwd = res->getString("password");
        }

        delete res;
        delete prep_stmt;
        delete conn;

        return pwd;

    }
    catch (sql::SQLException & e) {
        cout << "# ERR: " << e.what();
    }
}