eelua
=====

���� [EverEdit](http://www.everedit.net/) �༭���� lua �ű�������档

����
-------------------

    1. ��װ������ EverEdit �ṩ��һЩ�ӿ�
    2. �ڲ˵�����ʾ�ض�Ŀ¼�µĽű��ļ������ѡ���ִ��
    3. ע���ݼ�����󶨿�ݼ���ִ�нű�
    4. �ṩ��һ�� `dofile` �ӿڣ�������ģʽ�ļ��е���ִ�� lua �ű�
    5. �������๦��½��������...

ϵͳҪ��
-------------------

ʹ�� mingw �� premake5 ���б���

- [mingw](http://www.mingw.org/)
- [premake5](https://github.com/premake/premake-core)

����
----------------

```
premake5 gmake
make
```

��װ
----------------

�ڷ���ҳ����ƽ̨���ض�Ӧ�� ezip �ļ���ֱ���ϵ� EverEdit �༭����ʾ��װ���ɡ�

```
EverEdit/
  everedit.exe
  lua51.dll
  plugin/
    eelua.dll
  eelua/
    eelua_init.lua  # ������ʼ���ű�
    eeluarc.lua  # �û��Զ������ýű�
    plugins/  # �Զ������ű�
    scripts/  # ��ʾ�� ����չ�� -> ������� -> ��lua scripts�� �µĽű��ļ�
```

��Ҫ c ��������� `eelua.dll` �޸Ķ�����Ҫ���£�Ҳ����˵����ֻ�����и��� eelua �ű�Ŀ¼��

ʹ��
----------------

���Բο� scripts Ŀ¼��ʾ�����ӿ��ĵ����ڸ����У�Ҳ���Բ鿴Դ���˽�ӿ�ʹ�á�

TODO
----------------

License
----------------

eelua is made available under the terms of MIT license. See the LICENSE file that accompanies this distribution for the full text of the license.
