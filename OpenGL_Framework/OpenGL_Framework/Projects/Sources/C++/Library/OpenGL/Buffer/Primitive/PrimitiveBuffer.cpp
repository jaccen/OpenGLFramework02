/* ヘッダファイル */
#include "PrimitiveBuffer.h"


//-------------------------------------------------------------
//!
//! @brief OpenGL
//! @brief OpenGL関連の名前空間
//!
//-------------------------------------------------------------
namespace OpenGL
{

    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_PrimitiveBuffer::~C_PrimitiveBuffer()
    {
        glDeleteBuffers(1, &vertexBufferObjectHandle_);
        glDeleteBuffers(1, &indexBufferObjectHandle_);
        glDeleteVertexArrays(1, &vertexArrayObjectHandle_);
    }


    /*************************************************************//**
     *
     *  @brief  頂点配列オブジェクトハンドルを取得する
     *  @param  なし
     *  @return 頂点配列オブジェクトハンドル
     *
     ****************************************************************/
    VertexArrayObjectHandle C_PrimitiveBuffer::GetVertexArrayObjectHandle() const
    {
        return vertexArrayObjectHandle_;
    }


    /*************************************************************//**
     *
     *  @brief  インデックスバッファオブジェクトハンドルを取得する
     *  @param  なし
     *  @return インデックスバッファオブジェクトハンドル
     *
     ****************************************************************/
    VertexArrayObjectHandle C_PrimitiveBuffer::GetIndexBufferObjectHandle() const
    {
        return indexBufferObjectHandle_;
    }


    /*************************************************************//**
     *
     *  @brief  頂点数を取得する
     *  @param  なし
     *  @return 頂点数
     *
     ****************************************************************/
    uint32_t C_PrimitiveBuffer::GetVertexCount() const
    {
        return vertexCount_;
    }


    /*************************************************************//**
     *
     *  @brief  インデックス数を取得する
     *  @param  なし
     *  @return インデックス数
     *
     ****************************************************************/
    uint32_t C_PrimitiveBuffer::GetIndexCount() const
    {
        return indexCount_;
    }
}

