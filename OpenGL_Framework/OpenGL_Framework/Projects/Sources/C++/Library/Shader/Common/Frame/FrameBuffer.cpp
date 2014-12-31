/* ヘッダファイル */
#include "FrameBuffer.h"


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
    //! @brief コモン
    //! @brief 共通関連の名前空間
    //!
    //-------------------------------------------------------------
    namespace Common
    {
        /*************************************************************//**
         *
         *  @brief  コンストラクタ
         *  @param  バッファのサイズ
         *  @param  バッファの種類
         *  @param  ピクセルデータの種類
         *  @param  バッファ生成時に用いる関数
         *  @param  バッファの数
         *
         ****************************************************************/
        C_FrameBuffer::C_FrameBuffer(S_BufferSize bufferSizes[],
                                     ecBufferType bufferTypes[],
                                     ecPixelDataType pixelDataTypes[],
                                     CreateBufferFunction pCreateBufferFunctions[],
                                     uint32_t bufferCount)
        {
            // レンダーバッファデータをメモリを確保
            renderBufferDatas_.resize(bufferCount);

            for (size_t i = 0; i < bufferCount; ++i)
            {
                // データをコピー
                renderBufferDatas_[i].size_ = bufferSizes[i];
                renderBufferDatas_[i].type_ = bufferTypes[i];
                renderBufferDatas_[i].pixelDataType_ = pixelDataTypes[i];

                // 各バッファを生成
                pCreateBufferFunctions[i](&renderBufferDatas_[i].handle_, &renderBufferDatas_[i].size_);
            }

            // カラーバッファのリストとカラーをアタッチした数
            std::vector<GLenum> colorBufferList(bufferCount);
            uint32_t colorAttachmentCount = -1;

            // アタッチする種類を判別する関数
            static auto s_DistinctionAttachmentType = [&](ecPixelDataType pixelDataType)
            {
                if (pixelDataType == ecPixelDataType::COLOR)
                {
                    ++colorAttachmentCount;
                    return GL_COLOR_ATTACHMENT0 + colorAttachmentCount;
                }
                else if (pixelDataType == ecPixelDataType::DEPTH)
                {
                    return static_cast<uint32_t>(GL_DEPTH_ATTACHMENT);
                }
                else
                {
                    return static_cast<uint32_t>(GL_STENCIL_ATTACHMENT);
                }
            };

            // フレームバッファオブジェクトを生成し、バインド
            glGenFramebuffers(1, &frameBufferObjectHandle_);
            glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObjectHandle_);

            for (size_t i = 0; i < bufferCount; ++i)
            {
                // アタッチする種類を取得
                uint32_t attachmentType = s_DistinctionAttachmentType(renderBufferDatas_[i].pixelDataType_);

                if (renderBufferDatas_[i].type_ == ecBufferType::RENDER)
                {
                    glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                                              attachmentType,
                                              GL_RENDERBUFFER,
                                              renderBufferDatas_[i].handle_);
                }
                else
                {
                    glFramebufferTexture2D(GL_FRAMEBUFFER,
                                           attachmentType,
                                           GL_TEXTURE_2D,
                                           renderBufferDatas_[i].handle_,
                                           0);
                }

                if (attachmentType == (GL_COLOR_ATTACHMENT0 + colorAttachmentCount))
                {
                    colorBufferList.push_back(attachmentType);
                }
                else
                {
                    colorBufferList.push_back(GL_NONE);
                }
            }

            // カラーバッファのリストを設定
            glDrawBuffers(colorBufferList.size(), colorBufferList.data());

            // フレームバッファをアンバインド
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }


        /*************************************************************//**
         *
         *  @brief  デストラクタ
         *  @param  なし
         *
         ****************************************************************/
        C_FrameBuffer::~C_FrameBuffer()
        {
            // レンダーバッファを破棄
            for (size_t i = 0, bufferSize = renderBufferDatas_.size(); i < bufferSize; ++i)
            {
                if (renderBufferDatas_[i].type_ == ecBufferType::RENDER)
                {
                    glDeleteRenderbuffers(1, &renderBufferDatas_[i].handle_);
                }
                else
                {
                    glDeleteTextures(1, &renderBufferDatas_[i].handle_);
                }
            }

            // フレームバッファオブジェクトを破棄
            glDeleteFramebuffers(1, &frameBufferObjectHandle_);
        }


        /*************************************************************//**
         *
         *  @brief  フレームバッファをバインドする
         *  @param  なし
         *  @return なし
         *
         ****************************************************************/
        void C_FrameBuffer::Bind()
        {
            glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObjectHandle_);
        }


        /*************************************************************//**
         *
         *  @brief  フレームバッファをアンバインドする
         *  @param  なし
         *  @return なし
         *
         ****************************************************************/
        void C_FrameBuffer::Unbind()
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }


        /*************************************************************//**
         *
         *  @brief  レンダーバッファデータを取得する
         *  @param  インデックス
         *  @return レンダーバッファデータ
         *
         ****************************************************************/
        const S_RenderBufferData& C_FrameBuffer::GetRenderBufferData(uint32_t index) const
        {
            assert(index < renderBufferDatas_.size());

            return renderBufferDatas_[index];
        }
    }
}