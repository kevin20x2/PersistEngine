#pragma once
#include <FrameWork/Common/String.hpp>

namespace Persist
{

enum class ENMHlslToken
{
    // Control
    Invalid,
    Pragma,
    // operators
    Plus ,
    PlusEqual,
    Minus , 
    MinusEqual,
    Times,
    TimesEqual, 
    Div,
    DivEqual,
    Mod,
    ModEqual,
    LeftParenthesis,
    RightParenthesis,


    // logical
    EqualEqual , 
    NotEqual,
    Lower,
    LowerEqual,
    Greater,
    GreaterEqual,
    AndAnd,
    OrOr,

    // stateMent Keyword
    Assign ,  // "="
    LeftBrace ,
    RightBrace,
    Semicolon ,  // ;
    If ,
    Else ,
    For,
    While,
    Do , 
    Return,
    Switch,
    Case ,
    Break,
    Default , 
    Continue,
    Goto , 

    // Unary
    PlusPlus,
    MinusMinus,

    // Types
    Void,
    Const,
    Precise,

    Bool,

    Int,
    Int1,
    Int2,
    Int3,
    Int4,
    Int1x1,
    Int1x2,
    Int1x3,
    Int1x4,
    Int2x1,
    Int2x2,
    Int2x3,
    Int2x4,
    Int3x1,
    Int3x2,
    Int3x3,
    Int3x4,
    Int4x1,
    Int4x2,
    Int4x3,
    Int4x4,

    Half,
    Half1,
    Half2,
    Half3,
    Half4,
    Half1x1,
    Half1x2,
    Half1x3,
    Half1x4,
    Half2x1,
    Half2x2,
    Half2x3,
    Half2x4,
    Half3x1,
    Half3x2,
    Half3x3,
    Half3x4,
    Half4x1,
    Half4x2,
    Half4x3,
    Half4x4,

    Float,
    Float1,
    Float2,
    Float3,
    Float4,
    Float1x1,
    Float1x2,
    Float1x3,
    Float1x4,
    Float2x1,
    Float2x2,
    Float2x3,
    Float2x4,
    Float3x1,
    Float3x2,
    Float3x3,
    Float3x4,
    Float4x1,
    Float4x2,
    Float4x3,
    Float4x4,


    // sampler

    Texture,
    Texture2D,
    Texture3D, 

    Sampler,
    Sampler2D,

    In,
    Out,
    InOut,
    Static,
    Uniform,

    // Misc
    LeftSquareBracket,
    RightSquareBracket,
    Question ,  // "?"
    ColonColon , // "::"
    Colon , // ":"
    Comma , // ","
    Dot , // "."
    Struct,
    CBuffer ,
    Register ,

    Identifier,
    UnsignedIntegerConstant,
    FloatConstant,
    BoolConstantTrue,
    BoolConstantFalse,
    StringConstant,
};

struct SourceInfo
{
    String * fileName_;
    uint32_t lineNum_;
    //uin32_t colum
    SourceInfo() : fileName_(nullptr) ,lineNum_(0){}
};

struct HlslToken
{
    ENMHlslToken token_;
    String string_;
    uint32_t integer_;
    SourceInfo info_;

    explicit HlslToken(const String & identifier) : token_(ENMHlslToken::Identifier),string_(identifier) ,integer_(0) {}
    explicit HlslToken(ENMHlslToken inToken ,const String & identifier) : token_(inToken),string_(identifier) ,integer_(0) {}
    explicit HlslToken(uint32_t value) : token_(ENMHlslToken::UnsignedIntegerConstant),string_(""),integer_(value) {}
    //explicit HlslToken(bool value) : token_(ENMHlslToken::BoolConstant),string_(value?"true":"false"),integer_(value ? 1 : 0 ){};

};


}