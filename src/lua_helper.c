// Copyright (C) 2020 by Larry Xu
//
// This file is part of eelua, distributed under the MIT License.
// For full terms see the included LICENSE file.

#include "lua_helper.h"

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#include "util.h"

static int
msghandler(lua_State *L)
{
    const char *msg = lua_tostring(L, 1);
    if (msg == NULL) {  /* is error object not a string? */
        if (luaL_callmeta(L, 1, "__tostring")  /* does it have a metamethod */
            && lua_type(L, -1) == LUA_TSTRING) {  /* that produces a string? */
            return 1;  /* that is the message */
        } else {
            msg = lua_pushfstring(L, "(error object is a %s value)",
                                  luaL_typename(L, 1));
        }
    }
    luaL_traceback(L, L, msg, 1);  /* append a standard traceback */
    return 1;  /* return the traceback */
}


static int
luaH_report(lua_State *L, int rc)
{
    if (rc != LUA_OK) {
        const char *errmsg = lua_tostring(L, -1);
        ReportLuaError(errmsg);
        lua_pop(L, 1);
    }
    return rc;
}


int
luaH_docall(lua_State *L, int narg, int nres, const char *extra_msg)
{
    // ջ���Ǻ����Ӳ����б�
    int base = lua_gettop(L) - narg;  // ����λ��
    lua_pushcfunction(L, msghandler);
    lua_insert(L, base);  // ���� msghandler
    int rc = lua_pcall(L, narg, nres, base);  // ���ú�����ջ��Ϊ����б�������Ϣ
    lua_remove(L, base);  // �Ƴ� msghandler
    // NOTE: �ú�������������Ϣ����Ҫ���д���
    return rc;
}


static int
luaH_dochunk(lua_State *L, int rc)
{
    // ջ����chunk�������ߴ�����Ϣ
    // �ɹ�ջ��Ϊ���ؽ���б�
    // ʧ��ʱ�ָ�Ϊ����ǰ��������Ϣ���Ƴ���
    if (rc == LUA_OK) {
        rc = luaH_docall(L, 0, 0, NULL);
    }
    return luaH_report(L, rc);
}


int
luaH_dofile(lua_State *L, const char *fname)
{
    return luaH_dochunk(L, luaL_loadfile(L, fname));
}


int
luaH_dostring(lua_State *L, const char *code)
{
    return luaH_dochunk(L, luaL_loadstring(L, code));
}
