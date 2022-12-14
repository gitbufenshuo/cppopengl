// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: mc/comm/pbtexture.proto

#include "mc/comm/pbtexture.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

namespace mc {
namespace comm {
PROTOBUF_CONSTEXPR PBTexture::PBTexture(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.image_list_)*/{}
  , /*decltype(_impl_.image_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.magfilter_)*/0
  , /*decltype(_impl_.minfilter_)*/0
  , /*decltype(_impl_.wraps_)*/0
  , /*decltype(_impl_.wrapt_)*/0
  , /*decltype(_impl_.wrapr_)*/0
  , /*decltype(_impl_.texture_type_)*/0
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct PBTextureDefaultTypeInternal {
  PROTOBUF_CONSTEXPR PBTextureDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~PBTextureDefaultTypeInternal() {}
  union {
    PBTexture _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 PBTextureDefaultTypeInternal _PBTexture_default_instance_;
}  // namespace comm
}  // namespace mc
static ::_pb::Metadata file_level_metadata_mc_2fcomm_2fpbtexture_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_mc_2fcomm_2fpbtexture_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_mc_2fcomm_2fpbtexture_2eproto = nullptr;

const uint32_t TableStruct_mc_2fcomm_2fpbtexture_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBTexture, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBTexture, _impl_.magfilter_),
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBTexture, _impl_.minfilter_),
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBTexture, _impl_.wraps_),
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBTexture, _impl_.wrapt_),
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBTexture, _impl_.image_),
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBTexture, _impl_.wrapr_),
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBTexture, _impl_.image_list_),
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBTexture, _impl_.texture_type_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::mc::comm::PBTexture)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::mc::comm::_PBTexture_default_instance_._instance,
};

const char descriptor_table_protodef_mc_2fcomm_2fpbtexture_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\027mc/comm/pbtexture.proto\022\007mc.comm\"\227\001\n\tP"
  "BTexture\022\021\n\tmagFilter\030\001 \001(\005\022\021\n\tminFilter"
  "\030\002 \001(\005\022\r\n\005wrapS\030\003 \001(\005\022\r\n\005wrapT\030\004 \001(\005\022\r\n\005"
  "image\030\005 \001(\t\022\r\n\005wrapR\030\006 \001(\005\022\022\n\nimage_list"
  "\030\007 \003(\t\022\024\n\014texture_type\030\010 \001(\005B\tZ\007mc/commb"
  "\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_mc_2fcomm_2fpbtexture_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_mc_2fcomm_2fpbtexture_2eproto = {
    false, false, 207, descriptor_table_protodef_mc_2fcomm_2fpbtexture_2eproto,
    "mc/comm/pbtexture.proto",
    &descriptor_table_mc_2fcomm_2fpbtexture_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_mc_2fcomm_2fpbtexture_2eproto::offsets,
    file_level_metadata_mc_2fcomm_2fpbtexture_2eproto, file_level_enum_descriptors_mc_2fcomm_2fpbtexture_2eproto,
    file_level_service_descriptors_mc_2fcomm_2fpbtexture_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_mc_2fcomm_2fpbtexture_2eproto_getter() {
  return &descriptor_table_mc_2fcomm_2fpbtexture_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_mc_2fcomm_2fpbtexture_2eproto(&descriptor_table_mc_2fcomm_2fpbtexture_2eproto);
namespace mc {
namespace comm {

// ===================================================================

class PBTexture::_Internal {
 public:
};

PBTexture::PBTexture(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:mc.comm.PBTexture)
}
PBTexture::PBTexture(const PBTexture& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  PBTexture* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.image_list_){from._impl_.image_list_}
    , decltype(_impl_.image_){}
    , decltype(_impl_.magfilter_){}
    , decltype(_impl_.minfilter_){}
    , decltype(_impl_.wraps_){}
    , decltype(_impl_.wrapt_){}
    , decltype(_impl_.wrapr_){}
    , decltype(_impl_.texture_type_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.image_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.image_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_image().empty()) {
    _this->_impl_.image_.Set(from._internal_image(), 
      _this->GetArenaForAllocation());
  }
  ::memcpy(&_impl_.magfilter_, &from._impl_.magfilter_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.texture_type_) -
    reinterpret_cast<char*>(&_impl_.magfilter_)) + sizeof(_impl_.texture_type_));
  // @@protoc_insertion_point(copy_constructor:mc.comm.PBTexture)
}

inline void PBTexture::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.image_list_){arena}
    , decltype(_impl_.image_){}
    , decltype(_impl_.magfilter_){0}
    , decltype(_impl_.minfilter_){0}
    , decltype(_impl_.wraps_){0}
    , decltype(_impl_.wrapt_){0}
    , decltype(_impl_.wrapr_){0}
    , decltype(_impl_.texture_type_){0}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.image_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.image_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

PBTexture::~PBTexture() {
  // @@protoc_insertion_point(destructor:mc.comm.PBTexture)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void PBTexture::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.image_list_.~RepeatedPtrField();
  _impl_.image_.Destroy();
}

void PBTexture::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void PBTexture::Clear() {
// @@protoc_insertion_point(message_clear_start:mc.comm.PBTexture)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.image_list_.Clear();
  _impl_.image_.ClearToEmpty();
  ::memset(&_impl_.magfilter_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.texture_type_) -
      reinterpret_cast<char*>(&_impl_.magfilter_)) + sizeof(_impl_.texture_type_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* PBTexture::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int32 magFilter = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.magfilter_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int32 minFilter = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          _impl_.minfilter_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int32 wrapS = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 24)) {
          _impl_.wraps_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int32 wrapT = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 32)) {
          _impl_.wrapt_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // string image = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 42)) {
          auto str = _internal_mutable_image();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "mc.comm.PBTexture.image"));
        } else
          goto handle_unusual;
        continue;
      // int32 wrapR = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 48)) {
          _impl_.wrapr_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // repeated string image_list = 7;
      case 7:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 58)) {
          ptr -= 1;
          do {
            ptr += 1;
            auto str = _internal_add_image_list();
            ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
            CHK_(ptr);
            CHK_(::_pbi::VerifyUTF8(str, "mc.comm.PBTexture.image_list"));
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<58>(ptr));
        } else
          goto handle_unusual;
        continue;
      // int32 texture_type = 8;
      case 8:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 64)) {
          _impl_.texture_type_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* PBTexture::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:mc.comm.PBTexture)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 magFilter = 1;
  if (this->_internal_magfilter() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(1, this->_internal_magfilter(), target);
  }

  // int32 minFilter = 2;
  if (this->_internal_minfilter() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(2, this->_internal_minfilter(), target);
  }

  // int32 wrapS = 3;
  if (this->_internal_wraps() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(3, this->_internal_wraps(), target);
  }

  // int32 wrapT = 4;
  if (this->_internal_wrapt() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(4, this->_internal_wrapt(), target);
  }

  // string image = 5;
  if (!this->_internal_image().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_image().data(), static_cast<int>(this->_internal_image().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "mc.comm.PBTexture.image");
    target = stream->WriteStringMaybeAliased(
        5, this->_internal_image(), target);
  }

  // int32 wrapR = 6;
  if (this->_internal_wrapr() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(6, this->_internal_wrapr(), target);
  }

  // repeated string image_list = 7;
  for (int i = 0, n = this->_internal_image_list_size(); i < n; i++) {
    const auto& s = this->_internal_image_list(i);
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      s.data(), static_cast<int>(s.length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "mc.comm.PBTexture.image_list");
    target = stream->WriteString(7, s, target);
  }

  // int32 texture_type = 8;
  if (this->_internal_texture_type() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(8, this->_internal_texture_type(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:mc.comm.PBTexture)
  return target;
}

size_t PBTexture::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:mc.comm.PBTexture)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated string image_list = 7;
  total_size += 1 *
      ::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(_impl_.image_list_.size());
  for (int i = 0, n = _impl_.image_list_.size(); i < n; i++) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
      _impl_.image_list_.Get(i));
  }

  // string image = 5;
  if (!this->_internal_image().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_image());
  }

  // int32 magFilter = 1;
  if (this->_internal_magfilter() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_magfilter());
  }

  // int32 minFilter = 2;
  if (this->_internal_minfilter() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_minfilter());
  }

  // int32 wrapS = 3;
  if (this->_internal_wraps() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_wraps());
  }

  // int32 wrapT = 4;
  if (this->_internal_wrapt() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_wrapt());
  }

  // int32 wrapR = 6;
  if (this->_internal_wrapr() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_wrapr());
  }

  // int32 texture_type = 8;
  if (this->_internal_texture_type() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_texture_type());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData PBTexture::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    PBTexture::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*PBTexture::GetClassData() const { return &_class_data_; }


void PBTexture::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<PBTexture*>(&to_msg);
  auto& from = static_cast<const PBTexture&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:mc.comm.PBTexture)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_impl_.image_list_.MergeFrom(from._impl_.image_list_);
  if (!from._internal_image().empty()) {
    _this->_internal_set_image(from._internal_image());
  }
  if (from._internal_magfilter() != 0) {
    _this->_internal_set_magfilter(from._internal_magfilter());
  }
  if (from._internal_minfilter() != 0) {
    _this->_internal_set_minfilter(from._internal_minfilter());
  }
  if (from._internal_wraps() != 0) {
    _this->_internal_set_wraps(from._internal_wraps());
  }
  if (from._internal_wrapt() != 0) {
    _this->_internal_set_wrapt(from._internal_wrapt());
  }
  if (from._internal_wrapr() != 0) {
    _this->_internal_set_wrapr(from._internal_wrapr());
  }
  if (from._internal_texture_type() != 0) {
    _this->_internal_set_texture_type(from._internal_texture_type());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void PBTexture::CopyFrom(const PBTexture& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:mc.comm.PBTexture)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PBTexture::IsInitialized() const {
  return true;
}

void PBTexture::InternalSwap(PBTexture* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  _impl_.image_list_.InternalSwap(&other->_impl_.image_list_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.image_, lhs_arena,
      &other->_impl_.image_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(PBTexture, _impl_.texture_type_)
      + sizeof(PBTexture::_impl_.texture_type_)
      - PROTOBUF_FIELD_OFFSET(PBTexture, _impl_.magfilter_)>(
          reinterpret_cast<char*>(&_impl_.magfilter_),
          reinterpret_cast<char*>(&other->_impl_.magfilter_));
}

::PROTOBUF_NAMESPACE_ID::Metadata PBTexture::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_mc_2fcomm_2fpbtexture_2eproto_getter, &descriptor_table_mc_2fcomm_2fpbtexture_2eproto_once,
      file_level_metadata_mc_2fcomm_2fpbtexture_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace comm
}  // namespace mc
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::mc::comm::PBTexture*
Arena::CreateMaybeMessage< ::mc::comm::PBTexture >(Arena* arena) {
  return Arena::CreateMessageInternal< ::mc::comm::PBTexture >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
