/* ヘッダファイル */
#include "UniformBuffer.h"
#include "../../../OpenGL/OpenGlDefine.h"


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
        /*************************************************************//**
         *
         *  @brief  コンストラクタ
         *  @param  転送するバッファ
         *  @param  バッファのサイズ
         *  @param  ブロック名
         *  @param  修正の種類
         *
         ****************************************************************/
        C_UniformBuffer::C_UniformBuffer(void* pBuffer,
                                         uint32_t bufferSize,
                                         const std::string& rBlockName,
                                         OpenGL::ModifyEnum modifyType) :

            // ブロック名
            blockName_(rBlockName)

        {
            // ユニフォームバッファオブジェクトを作成し、バインド
            const int32_t CREWATE_BUFFER_NUMBER = 1;

            glGenBuffers(CREWATE_BUFFER_NUMBER, &handle_);
            glBindBuffer(OpenGL::Buffer::s_UNIFORM, handle_);

            // データを転送
            glBufferData(OpenGL::Buffer::s_UNIFORM, bufferSize, pBuffer, modifyType);

            // ユニフォームバッファオブジェクトをアンバインド
            glBindBuffer(OpenGL::Buffer::s_UNIFORM, 0);
        }


        /*************************************************************//**
         *
         *  @brief  デストラクタ
         *  @param  なし
         *
         ****************************************************************/
        C_UniformBuffer::~C_UniformBuffer()
        {
            // ユニフォームバッファーオブジェクトを破棄
            const int32_t DELETE_BUFFER_NUMBER = 1;

            glDeleteBuffers(DELETE_BUFFER_NUMBER, &handle_);
        }


        /*************************************************************//**
         *
         *  @brief  バッファの書き換えを行う
         *  @param  バッファ
         *  @param  バッファのサイズ
         *  @param  修正の種類
         *  @return なし
         *
         ****************************************************************/
        void C_UniformBuffer::Rewrite(void* pBuffer,
                                      uint32_t bufferSize,
                                      OpenGL::ModifyEnum modifyType)
        {
            // ユニフォームバッファオブジェクトをバインド
            glBindBuffer(OpenGL::Buffer::s_UNIFORM, handle_);

            // データを転送
            glBufferData(OpenGL::Buffer::s_UNIFORM, bufferSize, pBuffer, modifyType);

            // ユニフォームバッファオブジェクトをアンバインド
            glBindBuffer(OpenGL::Buffer::s_UNIFORM, 0);
        }


        /*************************************************************//**
         *
         *  @brief  プログラムオブジェクトからブロックのインデックスを取得する
         *  @param  なし
         *  @return ブロックのインデックス
         *
         ****************************************************************/
        UniformBufferObjectHandle C_UniformBuffer::GetBlockIndexFromProgramObject(ProgramObjectHandle programObjectHandle) const
        {
            return glGetUniformBlockIndex(programObjectHandle, blockName_.c_str());
        }


        /*************************************************************//**
         *
         *  @brief  ハンドルを取得する
         *  @param  なし
         *  @return ハンドル
         *
         ****************************************************************/
        UniformBufferObjectHandle C_UniformBuffer::GetHandle() const
        {
            return handle_;
        }


        /*************************************************************//**
         *
         *  @brief  生成処理を行う
         *  @param  バッファのサイズ
         *  @param  ブロック名
         *  @return ユニフォームバッファ
         *
         ****************************************************************/
        UniformBufferPtr C_UniformBuffer::s_Create(void* pBuffer,
                                                   uint32_t bufferSize,
                                                   const std::string& rBlockName,
                                                   OpenGL::ModifyEnum drawUsage)
        {
            return std::make_shared<C_UniformBuffer>(pBuffer, bufferSize, rBlockName, drawUsage);
        }
    }
}