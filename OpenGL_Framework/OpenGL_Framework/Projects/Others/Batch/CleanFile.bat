:: [ �o�b�`�t�@�C������ ]
:: ���s����ƃv���W�F�N�g���̕s�v�ȃt�H���_�ƃt�@�C�����폜����܂��B
:: �폜�����t�H���_�͂��̊K�w����Debug, Release, ipch�t�H���_�ł��B
:: �܂��A�c.ncb, �c.suo, �c.user, �c.sdf ���g���q�̃t�@�C���������ɍ폜����܂��B


:: ���s���̃R�}���h���\��
@echo off


echo �v���W�F�N�g�̕s�v�ȃt�@�C���ƃt�H���_���폜���܂��B

:: �s�v�ȃt�@�C���ƃt�H���_���폜
call :delfiles

echo �폜���������܂����B

:: �L�[���͂�ҋ@
pause


exit /b


:sub


cd %1
call :delfiles
cd ..


exit /b


:: �s�v�ȃt�H���_�ƃt�@�C�����폜����T�u���[�`��
:delfiles


if exist Debug rmdir /s /q Debug
if exist Release rmdir /s /q Release
if exist ipch rmdir /s /q ipch
if exist *.ncb del *.ncb
if exist *.suo del /A:H *.suo
if exist *.user del *.user
if exist *.sdf del *.sdf
if exist *.opensdf del /A:H *.opensdf


exit /b


:: [ ���� ]
:: if exist �t�@�C���� �ł��̃t�@�C�������݂����true
:: rmdir �͂��̃t�H���_���폜�B
:: ���̌��/s�����邱�Ƃł��̃t�H���_�����t�@�C�������ׂč폜�B
:: /q�����邱�Ƃō폜���̊m�F���Ȃ��ɂ���B
:: /A:H�͉B���t�@�C���ł��邱�Ƃ������B