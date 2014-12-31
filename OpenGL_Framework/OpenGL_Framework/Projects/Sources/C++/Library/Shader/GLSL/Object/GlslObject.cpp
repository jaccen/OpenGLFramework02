/* ヘッダファイル */
#include "GlslObject.h"
#include "../../../Common/CommonHelper.h"
#include "../../../Debug/Helper/DebugHelper.h"
#include "../../../Math/MathAll.h"
#include <fstream>


//-------------------------------------------------------------
//!
//! @brief シェーダー
//! @brief シェーダー関連の名前空間
//!
//-------------------------------------------------------------
namespace Shader
{
    //-------------------------------------------------------------
    //!
    //! @brief GLSL
    //! @brief GLSL関連の名前空間
    //!
    //-------------------------------------------------------------
    namespace GLSL
    {
        namespace
        {
            const int32_t s_UNIFORM_LOCATION_ERROR_VELUE = -1;              ///< @brief ユニフォーム変数の場所のエラー値
        }

        /*************************************************************//**
         *
         *  @brief  コンストラクタ
         *  @param  なし
         *
         ****************************************************************/
        C_GlslObject::C_GlslObject()
        {
        }


        /*************************************************************//**
         *
         *  @brief  デストラクタ
         *  @param  なし
         *
         ****************************************************************/
        C_GlslObject::~C_GlslObject()
        {
            if (programObjectHandle_ != 0) Delete();
        }


        /*************************************************************//**
         *
         *  @brief  ファイルからシェーダーをコンパイルする
         *  @param  ファイルパス
         *  @param  シェーダーの種類
         *  @return 正常終了：true
         *  @return 異常終了：false
         *
         ****************************************************************/
        bool C_GlslObject::CompileFromFile(const std::string& rFilePath, TypeEnum type)
        {
            // ファイルを開く
            std::ifstream file(rFilePath);

            if (file.fail() == true)
            {
                PrintLog("[ C_GlslObject::CompileFromFile ] : ファイルを開くのに失敗しました。\n");
                PrintLog("                       ファイル名 : %s", rFilePath.c_str());

                return false;
            }

            // サイズを取得
            uint32_t fileSize = Common::C_CommonHelper::s_GetFileSize(&file);

            if (fileSize == 0)
            {
                PrintLog("[ C_GlslObject::CompileFromFile ] : ファイルの中身がありません。\n");

                return false;
            }

            // ソースのメモリ領域を確保し、末尾に\0を入れる
            auto pSource = std::make_unique<char[]>(fileSize + 1);
            pSource[fileSize] = '\0';

            // ソースのカウンタ
            size_t sourceCount = 0;

            while (true)
            {
                // ソースを読み取る
                pSource[sourceCount] = file.get();

                // ファイルが末尾の場合はループを抜ける
                if (file.eof() == true) break;

                // カウンタを1増加
                ++sourceCount;
            }

            // ソースの末尾に再度\0を入れる
            pSource[sourceCount] = '\0';

            // ソースをコンパイル
            if (CompileFromString(pSource.get(), type) == false)
            {
                PrintLog("[ C_GlslObject::CompileFromFile ] : シェーダーのコンパイルに失敗しました。\n");

                return false;
            }

            return true;
        }


        /*************************************************************//**
         *
         *  @brief  文字列からシェーダーをコンパイルする
         *  @param  文字列( ソース )
         *  @param  シェーダーの種類
         *  @return 正常終了：true
         *  @return 異常終了：false
         *
         ****************************************************************/
        bool C_GlslObject::CompileFromString(const std::string& rString, TypeEnum type)
        {
            assert(rString.empty() == false);

            // シェーダーオブジェクトハンドル
            ShaderObjectHandle shaderObjectHandle = 0;

            // シェーダーオブジェクトを作成
            shaderObjectHandle = glCreateShader(type);

            if (shaderObjectHandle == 0)
            {
                PrintLog("[ C_GlslObject::CompileFromString ] : シェーダーオブジェクトの作成に失敗しました。\n");

                return false;
            }

            // シェーダーをまとめた配列
            const GLchar* pSourceArray[] = { rString.c_str() };

            // シェーダーオブジェクトハンドルにソースをコピー
            const int32_t SHADER_COPY_NUMBER = 1;

            glShaderSource(shaderObjectHandle, SHADER_COPY_NUMBER, pSourceArray, nullptr);

            // シェーダーのコンパイル
            glCompileShader(shaderObjectHandle);

            // コンパイルの結果
            GLint compileResult = 0;

            // シェーダーのステータスを取得
            glGetShaderiv(shaderObjectHandle, GL_COMPILE_STATUS, &compileResult);

            if (compileResult == GL_FALSE)
            {
                PrintLog("[ C_GlslObject::CompileFromString ] : シェーダーのコンパイルに失敗しました。\n");

                // エラーを出力
                PrintCompileError(shaderObjectHandle);

                return false;
            }

            // プログラムオブジェクトが作成されていない場合は作成
            if (programObjectHandle_ == 0)
            {
                programObjectHandle_ = glCreateProgram();

                if (programObjectHandle_ == 0)
                {
                    PrintLog("[ C_GlslObject::CompileFromString ] : プログラムオブジェクトの作成に失敗しました。\n");

                    return false;
                }
            }

            // シェーダーオブジェクトをプログラムオブジェクトに加え、削除フラグを立てる
            glAttachShader(programObjectHandle_, shaderObjectHandle);
            glDeleteShader(programObjectHandle_);

            return true;
        }


        /*************************************************************//**
        *
        *  @brief  シェーダーのリンクを行う
        *  @param  なし
        *  @return 正常終了：true
        *  @return 異常終了：false
        *
        ****************************************************************/
        bool C_GlslObject::Link()
        {
            assert(programObjectHandle_ != 0);

            // リンク済みの場合は何もしない
            if (linkFlag_ == true) return true;

            // プログラムをリンクする
            glLinkProgram(programObjectHandle_);

            // リンクの結果
            GLint linkResult = 0;

            // プログラムのステータスを取得
            glGetProgramiv(programObjectHandle_, GL_LINK_STATUS, &linkResult);

            if (linkResult == GL_FALSE)
            {
                PrintLog("[ C_GlslObject::Link ] : プログラムのリンクに失敗しました。\n");

                // エラーを出力
                PrintLinkError(programObjectHandle_);

                return false;
            }

            // リンク済みフラグを立てる
            linkFlag_ = true;

            return true;
        }


        /*************************************************************//**
        *
        *  @brief  アクティブな属性を出力する
        *  @param  なし
        *  @return なし
        *
        ****************************************************************/
        void C_GlslObject::PrintActiveAttribute()
        {
            // 属性の数と属性の名前の長さ
            GLint attributeNumber = 0, attributeNameLength = 0;

            // 属性の数と属性の名前の長さを取得
            glGetProgramiv(programObjectHandle_, GL_ACTIVE_ATTRIBUTES, &attributeNumber);
            glGetProgramiv(programObjectHandle_, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &attributeNameLength);

            // 属性の名前のメモリ領域を確保
            auto pAttiributeName = std::make_unique<GLchar[]>(attributeNameLength);

            std::cout << "[ C_GlslObject::PrintActiveAttributes ] : 頂点シェーダーの属性の情報" << std::endl;
            std::cout << " Location | Name" << std::endl;
            std::cout << "------------------------------------------------" << std::endl;

            for (int32_t i = 0; i < attributeNumber; ++i)
            {
                // 書き込まれた数
                GLsizei writtenNumber = 0;

                // サイズ
                GLint size = 0;

                // タイプ
                GLenum type;

                // 属性についての情報を取得
                glGetActiveAttrib(programObjectHandle_, i, attributeNameLength, &writtenNumber, &size, &type, pAttiributeName.get());
                GLint location = glGetAttribLocation(programObjectHandle_, pAttiributeName.get());

                // 属性についての情報を出力
                std::printf(" %-8d | %s\n", location, pAttiributeName.get());
            }
        }


        /*************************************************************//**
        *
        *  @brief  アクティブなユニフォーム変数を出力する
        *  @param  なし
        *  @return なし
        *
        ****************************************************************/
        void C_GlslObject::PrintActiveUniform()
        {
            // ユニフォーム変数の数とユニフォーム変数の名前の長さ
            GLint uniformNumber = 0, uniformNameLength = 0;

            // ユニフォーム変数の数を取得
            glGetProgramiv(programObjectHandle_, GL_ACTIVE_UNIFORMS, &uniformNumber);

            // ユニフォーム変数の名前の長さを取得
            glGetProgramiv(programObjectHandle_, GL_ACTIVE_UNIFORM_MAX_LENGTH, &uniformNameLength);

            // ユニフォーム変数の名前を格納するメモリ領域を確保
            auto pUniformName = std::make_unique<GLchar[]>(uniformNameLength);

            std::cout << "[ C_GlslObject::PrintActiveUniforms ] : ユニフォーム変数の情報" << std::endl;
            std::cout << " Location | Name" << std::endl;
            std::cout << "------------------------------------------------" << std::endl;

            for (int32_t i = 0; i < uniformNumber; ++i)
            {
                // 書き込まれた数
                GLsizei writtenNumber = 0;

                // サイズ
                GLint size = 0;

                // タイプ
                GLenum type;

                // 属性についての情報を取得
                glGetActiveUniform(programObjectHandle_, i, uniformNameLength, &writtenNumber, &size, &type, pUniformName.get());
                GLint location = glGetUniformLocation(programObjectHandle_, pUniformName.get());

                // 属性についての情報を出力
                std::printf(" %-8d | %s\n", location, pUniformName.get());
            }
        }


        /*************************************************************//**
        *
        *  @brief  シェーダーの使用を開始する
        *  @param  なし
        *  @return なし
        *
        ****************************************************************/
        void C_GlslObject::Begin()
        {
            assert(programObjectHandle_ != 0);

            glUseProgram(programObjectHandle_);
        }


        /*************************************************************//**
        *
        *  @brief  ユニフォームバッファを含めてシェーダーの使用を開始する
        *  @param  ユニフォームバッファ
        *          注：( シェーダー利用中に破棄されない領域に作成したものを使うこと )
        *  @return なし
        *
        ****************************************************************/
        void C_GlslObject::BeginWithUnifomBuffer(UniformBufferObjectHandle uniformBufferObjectHandle, 
                                                 UniformBlockIndex uniformBlockIndex)
        {
            // シェーダーの使用開始
            Begin();

            // ユニフォームバッファオブジェクトをバインド
            glBindBufferBase(BufferType::s_UNIFORM, uniformBlockIndex, uniformBufferObjectHandle);
        }


        /*************************************************************//**
        *
        *  @brief  シェーダーの使用を終了する
        *  @param  なし
        *  @return なし
        *
        ****************************************************************/
        void C_GlslObject::End()
        {
            glUseProgram(0);
        }


        /*************************************************************//**
        *
        *  @brief  シェーダーの削除を行う
        *  @param  なし
        *  @return なし
        *
        ****************************************************************/
        void C_GlslObject::Delete()
        {
            // プログラムオブジェクトの削除
            glDeleteProgram(programObjectHandle_);
            programObjectHandle_ = 0;

            // リンク済みか判断するフラグを下げる
            linkFlag_ = false;
        }


        /*************************************************************//**
        *
        *  @brief  int型の値でユニフォーム変数を設定する
        *  @param  ユニフォーム変数の名前
        *  @param  値
        *  @return 正常終了：true
        *  @return 異常終了：false
        *
        ****************************************************************/
        bool C_GlslObject::SetUniform1i(const std::string& rName, int32_t value)
        {
            // ユニフォーム変数の場所を取得
            int32_t location = GetUniformLocation(rName);

            if (location == s_UNIFORM_LOCATION_ERROR_VELUE)
            {
                PrintLog("[ C_GlslObject::SetUniform1i ] : ユニフォーム変数の場所の取得に失敗しました。\n");

                return false;
            }

            glUniform1i(location, value);

            return true;
        }


        /*************************************************************//**
        *
        *  @brief  float型の値でユニフォーム変数を設定する
        *  @param  ユニフォーム変数の名前
        *  @param  値
        *  @return 正常終了：true
        *  @return 異常終了：false
        *
        ****************************************************************/
        bool C_GlslObject::SetUniform1f(const std::string& rName, float value)
        {
            // ユニフォーム変数の場所を取得
            int32_t location = GetUniformLocation(rName);

            if (location == s_UNIFORM_LOCATION_ERROR_VELUE)
            {
                PrintLog("[ C_GlslObject::SetUniform1f ] : ユニフォーム変数の場所の取得に失敗しました。\n");

                return false;
            }

            glUniform1f(location, value);

            return true;
        }


        /*************************************************************//**
        *
        *  @brief  bool型の値でユニフォーム変数を設定する
        *  @param  ユニフォーム変数の名前
        *  @param  値
        *  @return 正常終了：true
        *  @return 異常終了：false
        *
        ****************************************************************/
        bool C_GlslObject::SetUniform1b(const std::string& rName, bool value)
        {
            // ユニフォーム変数の場所を取得
            int32_t location = GetUniformLocation(rName);

            if (location == s_UNIFORM_LOCATION_ERROR_VELUE)
            {
                PrintLog("[ C_GlslObject::SetUniform1b ] : ユニフォーム変数の場所の取得に失敗しました。\n");

                return false;
            }

            glUniform1i(location, value);

            return true;
        }


        /*************************************************************//**
        *
        *  @brief  float型の2つの値でユニフォーム変数を設定する
        *  @param  ユニフォーム変数の名前
        *  @param  値1
        *  @param  値2
        *  @return 正常終了：true
        *  @return 異常終了：false
        *
        ****************************************************************/
        bool C_GlslObject::SetUniform2f(const std::string& rName,
                                        float x,
                                        float y)
        {
            // ユニフォーム変数の場所を取得
            int32_t location = GetUniformLocation(rName);

            if (location == s_UNIFORM_LOCATION_ERROR_VELUE)
            {
                PrintLog("[ C_GlslObject::SetUniform2f ] : ユニフォーム変数の場所の取得に失敗しました。\n");

                return false;
            }

            glUniform2f(location, x, y);

            return true;
        }


        /*************************************************************//**
        *
        *  @brief  float型の3つの値でユニフォーム変数を設定する
        *  @param  ユニフォーム変数の名前
        *  @param  値1
        *  @param  値2
        *  @param  値3
        *  @return 正常終了：true
        *  @return 異常終了：false
        *
        ****************************************************************/
        bool C_GlslObject::SetUniform3f(const std::string& rName,
                                        float x,
                                        float y,
                                        float z)
        {
            // ユニフォーム変数の場所を取得
            int32_t location = GetUniformLocation(rName);

            if (location == s_UNIFORM_LOCATION_ERROR_VELUE)
            {
                PrintLog("[ C_GlslObject::SetUniform3f ] : ユニフォーム変数の場所の取得に失敗しました。\n");

                return false;
            }

            glUniform3f(location, x, y, z);

            return true;
        }


        /*************************************************************//**
        *
        *  @brief  float型の4つの値でユニフォーム変数を設定する
        *  @param  ユニフォーム変数の名前
        *  @param  値1
        *  @param  値2
        *  @param  値3
        *  @param  値4
        *  @return 正常終了：true
        *  @return 異常終了：false
        *
        ****************************************************************/
        bool C_GlslObject::SetUniform4f(const std::string& rName,
                                        float x,
                                        float y,
                                        float z,
                                        float w)
        {
            // ユニフォーム変数の場所を取得
            int32_t location = GetUniformLocation(rName);

            if (location == s_UNIFORM_LOCATION_ERROR_VELUE)
            {
                PrintLog("[ C_GlslObject::SetUniform4f ] : ユニフォーム変数の場所の取得に失敗しました。\n");

                return false;
            }

            glUniform4f(location, x, y, z, w);

            return true;
        }


        /*************************************************************//**
        *
        *  @brief  2Dベクトルでユニフォーム変数を設定する
        *  @param  ユニフォーム変数の名前
        *  @param  2Dベクトル
        *  @return 正常終了：true
        *  @return 異常終了：false
        *
        ****************************************************************/
        bool C_GlslObject::SetUniformVector2(const std::string& rName,
                                             const Math::S_Vector2<float>& rVector)
        {
            // ユニフォーム変数の場所を取得
            int32_t location = GetUniformLocation(rName);

            if (location == s_UNIFORM_LOCATION_ERROR_VELUE)
            {
                PrintLog("[ C_GlslObject::SetUniform4f ] : ユニフォーム変数の場所の取得に失敗しました。\n");

                return false;
            }

            glUniform2f(location, rVector.x_, rVector.y_);

            return true;
        }


        /*************************************************************//**
        *
        *  @brief  3Dベクトルでユニフォーム変数を設定する
        *  @param  ユニフォーム変数の名前
        *  @param  3Dベクトル
        *  @return 正常終了：true
        *  @return 異常終了：false
        *
        ****************************************************************/
        bool C_GlslObject::SetUniformVector3(const std::string& rName,
                                             const Math::S_Vector3<float>& rVector)
        {
            // ユニフォーム変数の場所を取得
            int32_t location = GetUniformLocation(rName);

            if (location == s_UNIFORM_LOCATION_ERROR_VELUE)
            {
                PrintLog("[ C_GlslObject::SetUniformVector3 ] : ユニフォーム変数の場所の取得に失敗しました。\n");

                return false;
            }

            glUniform3f(location, rVector.x_, rVector.y_, rVector.z_);

            return true;
        }


        /*************************************************************//**
        *
        *  @brief  4Dベクトルでユニフォーム変数を設定する
        *  @param  ユニフォーム変数の名前
        *  @param  4Dベクトル
        *  @return 正常終了：true
        *  @return 異常終了：false
        *
        ****************************************************************/
        bool C_GlslObject::SetUniformVector4(const std::string& rName,
                                             const Math::S_Vector4<float>& rVector)
        {
            // ユニフォーム変数の場所を取得
            int32_t location = GetUniformLocation(rName);

            if (location == s_UNIFORM_LOCATION_ERROR_VELUE)
            {
                PrintLog("[ C_GlslObject::SetUniformVector4 ] : ユニフォーム変数の場所の取得に失敗しました。\n");

                return false;
            }

            glUniform4f(location, rVector.x_, rVector.y_, rVector.z_, rVector.w_);

            return true;
        }


        /*************************************************************//**
        *
        *  @brief  3 * 3 の行列でユニフォーム変数を設定する
        *  @param  ユニフォーム変数の名前
        *  @param  3 * 3 の行列
        *  @param  要素数
        *  @return 正常終了：true
        *  @return 異常終了：false
        *
        ****************************************************************/
        bool C_GlslObject::SetUniformMatrix3x3(const std::string& rName,
                                               const Math::S_Matrix3x3<float>& rMatrix,
                                               int32_t elementCount)
        {
            // ユニフォーム変数の場所を取得
            int32_t location = GetUniformLocation(rName);

            if (location == s_UNIFORM_LOCATION_ERROR_VELUE)
            {
                PrintLog("[ C_GlslObject::SetUniformMatrix3 ] : ユニフォーム変数の場所の取得に失敗しました。\n");

                return false;
            }

            glUniformMatrix3fv(location, elementCount, GL_FALSE, rMatrix.a_);

            return true;
        }


        /*************************************************************//**
        *
        *  @brief  4 * 4 の行列でユニフォーム変数を設定する
        *  @param  ユニフォーム変数の名前
        *  @param  4 * 4 の行列
        *  @param  要素数
        *  @return 正常終了：true
        *  @return 異常終了：false
        *
        ****************************************************************/
        bool C_GlslObject::SetUniformMatrix4x4(const std::string& rName,
                                               const Math::S_Matrix4x4<float>& rMatrix,
                                               int32_t elementCount)
        {
            // ユニフォーム変数の場所を取得
            int32_t location = GetUniformLocation(rName);

            if (location == s_UNIFORM_LOCATION_ERROR_VELUE)
            {
                PrintLog("[ C_GlslObject::SetUniformMatrix4 ] : ユニフォーム変数の場所の取得に失敗しました。\n");

                return false;
            }

            glUniformMatrix4fv(location, elementCount, GL_FALSE, rMatrix.a_);

            return true;
        }


        /*************************************************************//**
        *
        *  @brief  サブルーチンのインデックスを取得する
        *  @param  シェーダーの種類
        *  @param  サブルーチン名
        *  @return サブルーチンのインデックス
        *
        ****************************************************************/
        SubroutineIndex C_GlslObject::GetSubroutineIndex(TypeEnum type, const std::string& rName)
        {
            assert(programObjectHandle_ != 0);

            return glGetSubroutineIndex(programObjectHandle_, type, rName.c_str());
        }


        /*************************************************************//**
        *
        *  @brief  アクティブなサブルーチンをバインドする
        *  @param  サブルーチンのインデックス
        *  @param  シェーダーの種類
        *  @return なし
        *
        ****************************************************************/
        void C_GlslObject::BindActiveSubroutine(SubroutineIndex index, TypeEnum type)
        {
            const int32_t BIND_SUBROUTINE_NUMBER = 1;

            glUniformSubroutinesuiv(type, BIND_SUBROUTINE_NUMBER, &index);
        }


        /*************************************************************//**
        *
        *  @brief  プログラムオブジェクトを取得する
        *  @param  なし
        *  @return プログラムオブジェクト
        *
        ****************************************************************/
        ProgramObjectHandle C_GlslObject::GetProgramObject() const
        {
            assert(programObjectHandle_ != 0);

            return programObjectHandle_;
        }


        /*************************************************************//**
        *
        *  @brief  リンク済みフラグを取得する
        *  @param  なし
        *  @return リンク済みフラグ
        *
        ****************************************************************/
        bool C_GlslObject::IsLinkFlag() const
        {
            return linkFlag_;
        }


        /*************************************************************//**
        *
        *  @brief  コンパイル時のエラーを出力する
        *  @param  なし
        *  @return なし
        *
        ****************************************************************/
        void C_GlslObject::PrintCompileError(ShaderObjectHandle handle)
        {
            // ログの長さ
            GLint logLength = 0;

            // ログの長さを問い合わせる
            glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &logLength);

            if (logLength > 0)
            {
                // ログのメモリ領域を確保
                auto pLog = std::make_unique<GLchar[]>(logLength);

                // 書き込まれた数
                GLsizei writtenNumber = 0;

                // ログの情報を取得
                glGetShaderInfoLog(handle, logLength, &writtenNumber, pLog.get());

                PrintLog("                    シェーダーログ : %s\n", pLog.get());
            }
        }


        /*************************************************************//**
        *
        *  @brief  リンク時のエラーを出力する
        *  @param  なし
        *  @return なし
        *
        ****************************************************************/
        void C_GlslObject::PrintLinkError(ProgramObjectHandle handle)
        {
            // ログの長さ
            GLint logLength = 0;

            // ログの長さを問い合わせる
            glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &logLength);

            if (logLength > 0)
            {
                // ログのメモリ領域を確保
                auto pLog = std::make_unique<GLchar[]>(logLength);

                // 書き込まれた数
                GLsizei writtenNumber = 0;

                // ログの情報を取得
                glGetProgramInfoLog(handle, logLength, &writtenNumber, pLog.get());

                PrintLog("          プログラムログ : %s\n", pLog.get());
            }
        }


        /*************************************************************//**
        *
        *  @brief  ユニフォーム変数の場所を取得する
        *  @param  ユニフォーム変数の名前
        *  @return なし
        *
        ****************************************************************/
        int32_t C_GlslObject::GetUniformLocation(const std::string& rName) const
        {
            assert(programObjectHandle_ != 0);

            return glGetUniformLocation(programObjectHandle_, rName.c_str());
        }
    }
}