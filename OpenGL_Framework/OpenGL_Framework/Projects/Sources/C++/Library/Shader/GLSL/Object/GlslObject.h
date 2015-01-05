/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../GlslDefine.h"
#include "../Uniform/UniformBuffer.h"
#include <vector>


/* 前方宣言 */
namespace Math
{
    template<typename T>
    struct S_Vector2;
    
    template<typename T>
    struct S_Vector3;
    
    template<typename T>
    struct S_Vector4;
    
    template<typename T>
    struct S_Matrix3x3;

    template<typename T>
    struct S_Matrix4x4;
};


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
        /* 前方宣言 */
        class C_GlslObject;


        /* 別名 */
        using GlslObjectPtr = std::shared_ptr<C_GlslObject>;                                        // GlslObjectPtr型


        //-------------------------------------------------------------
        //!
        //! @brief GLSLオブジェクト
        //! @brief GLSLデータを扱うためのクラス
        //!
        //-------------------------------------------------------------
        class C_GlslObject
        {
        public:
            C_GlslObject();                                                                         // コンストラクタ
            virtual ~C_GlslObject();                                                                // デストラクタ
            bool CompileFromFile(const std::string& rFilePath, TypeEnum type);                      // ファイルからコンパイル
            bool CompileFromString(const std::string& rString, TypeEnum type);                      // 文字列からコンパイル
            bool Link();                                                                            // リンク処理
            void PrintActiveAttribute();                                                            // アクティブな属性を出力
            void PrintActiveUniform();                                                              // アクティブなユニフォーム変数を出力
            void Begin();                                                                           // 使用開始
            void BeginWithUnifomBuffer(UniformBufferObjectHandle uniformBufferObjectHandle,         // ユニフォームバッファを利用して使用開始
                                       UniformBlockIndex uniformBlockIndex);       
            void End();                                                                             // 使用終了
            void Delete();                                                                          // 削除処理
            bool SetUniform1i(const std::string& rName, int32_t value);                             // int型の値でユニフォーム変数を設定
            bool SetUniform1f(const std::string& rName, float value);                               // float型の値でユニフォーム変数を設定
            bool SetUniform1b(const std::string& rName, bool value);                                // bool型の値でユニフォーム変数を設定
            bool SetUniform2f(const std::string& rName,                                             // float型の2つの値でユニフォーム変数を設定
                              float x,
                              float y);
            bool SetUniform3f(const std::string& rName,                                             // float型の3つの値でユニフォーム変数を設定
                              float x,
                              float y,
                              float z);
            bool SetUniform4f(const std::string& rName,                                             // float型の4つの値でユニフォーム変数を設定
                              float x,
                              float y,
                              float z,
                              float w);
            bool SetUniformVector2(const std::string& rName,                                        // 2Dベクトルでユニフォーム変数を設定
                                   const Math::S_Vector2<float>& rVector);
            bool SetUniformVector3(const std::string& rName,                                        // 3Dベクトルでユニフォーム変数を設定
                                   const Math::S_Vector3<float>& rVector);
            bool SetUniformVector4(const std::string& rName,                                        // 4Dベクトルでユニフォーム変数を設定
                                   const Math::S_Vector4<float>& rVector);
            bool SetUniformMatrix3x3(const std::string& rName,                                      // 3 * 3の行列でユニフォーム変数を設定
                                     const Math::S_Matrix3x3<float>& rMatrix,
                                     int32_t elementCount = 1);
            bool SetUniformMatrix4x4(const std::string& rName,                                      // 4 * 4の行列でユニフォーム変数を設定
                                     const Math::S_Matrix4x4<float>& rMatrix,
                                     int32_t elementCount = 1);
            SubroutineIndex GetSubroutineIndex(TypeEnum type, const std::string& rName);            // サブルーチンのインデックスを取得
            void BindActiveSubroutine(SubroutineIndex index, TypeEnum type);                        // アクティブなサブルーチンをバインド
            ProgramObjectHandle GetProgramObjectHandle() const;                                     // プログラムオブジェクトのハンドルを取得
            bool IsLinkFlag() const;                                                                // リンク済みフラグを取得

            static GlslObjectPtr s_Create();                                                        // 生成処理
        private:
            ProgramObjectHandle programObjectHandle_ = 0;                                           ///< @brief プログラムオブジェクトハンドル
            bool linkFlag_ = false;                                                                 ///< @brief リンク済みか判断するフラグ

            void PrintCompileError(ShaderObjectHandle handle);                                      // コンパイル時のエラーを出力
            void PrintLinkError(ProgramObjectHandle handle);                                        // リンク時のエラーを出力
            int32_t GetUniformLocation(const std::string& rName)  const;                            // ユニフォーム変数の場所を取得
        };
    }
}
