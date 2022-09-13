// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: mc/comm/pbshaderprogram.proto

#include "mc/comm/pbshaderprogram.pb.h"

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
PROTOBUF_CONSTEXPR PBShaderProgram::PBShaderProgram(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.vs_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.fs_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct PBShaderProgramDefaultTypeInternal {
  PROTOBUF_CONSTEXPR PBShaderProgramDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~PBShaderProgramDefaultTypeInternal() {}
  union {
    PBShaderProgram _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 PBShaderProgramDefaultTypeInternal _PBShaderProgram_default_instance_;
}  // namespace comm
}  // namespace mc
static ::_pb::Metadata file_level_metadata_mc_2fcomm_2fpbshaderprogram_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_mc_2fcomm_2fpbshaderprogram_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_mc_2fcomm_2fpbshaderprogram_2eproto = nullptr;

const uint32_t TableStruct_mc_2fcomm_2fpbshaderprogram_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBShaderProgram, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBShaderProgram, _impl_.vs_),
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBShaderProgram, _impl_.fs_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::mc::comm::PBShaderProgram)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::mc::comm::_PBShaderProgram_default_instance_._instance,
};

const char descriptor_table_protodef_mc_2fcomm_2fpbshaderprogram_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\035mc/comm/pbshaderprogram.proto\022\007mc.comm"
  "\")\n\017PBShaderProgram\022\n\n\002vs\030\001 \001(\t\022\n\n\002fs\030\002 "
  "\001(\tB\tZ\007mc/commb\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_mc_2fcomm_2fpbshaderprogram_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_mc_2fcomm_2fpbshaderprogram_2eproto = {
    false, false, 102, descriptor_table_protodef_mc_2fcomm_2fpbshaderprogram_2eproto,
    "mc/comm/pbshaderprogram.proto",
    &descriptor_table_mc_2fcomm_2fpbshaderprogram_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_mc_2fcomm_2fpbshaderprogram_2eproto::offsets,
    file_level_metadata_mc_2fcomm_2fpbshaderprogram_2eproto, file_level_enum_descriptors_mc_2fcomm_2fpbshaderprogram_2eproto,
    file_level_service_descriptors_mc_2fcomm_2fpbshaderprogram_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_mc_2fcomm_2fpbshaderprogram_2eproto_getter() {
  return &descriptor_table_mc_2fcomm_2fpbshaderprogram_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_mc_2fcomm_2fpbshaderprogram_2eproto(&descriptor_table_mc_2fcomm_2fpbshaderprogram_2eproto);
namespace mc {
namespace comm {

// ===================================================================

class PBShaderProgram::_Internal {
 public:
};

PBShaderProgram::PBShaderProgram(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:mc.comm.PBShaderProgram)
}
PBShaderProgram::PBShaderProgram(const PBShaderProgram& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  PBShaderProgram* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.vs_){}
    , decltype(_impl_.fs_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.vs_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.vs_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_vs().empty()) {
    _this->_impl_.vs_.Set(from._internal_vs(), 
      _this->GetArenaForAllocation());
  }
  _impl_.fs_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.fs_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_fs().empty()) {
    _this->_impl_.fs_.Set(from._internal_fs(), 
      _this->GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:mc.comm.PBShaderProgram)
}

inline void PBShaderProgram::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.vs_){}
    , decltype(_impl_.fs_){}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.vs_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.vs_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.fs_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.fs_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

PBShaderProgram::~PBShaderProgram() {
  // @@protoc_insertion_point(destructor:mc.comm.PBShaderProgram)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void PBShaderProgram::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.vs_.Destroy();
  _impl_.fs_.Destroy();
}

void PBShaderProgram::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void PBShaderProgram::Clear() {
// @@protoc_insertion_point(message_clear_start:mc.comm.PBShaderProgram)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.vs_.ClearToEmpty();
  _impl_.fs_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* PBShaderProgram::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string vs = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_vs();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "mc.comm.PBShaderProgram.vs"));
        } else
          goto handle_unusual;
        continue;
      // string fs = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_fs();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "mc.comm.PBShaderProgram.fs"));
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

uint8_t* PBShaderProgram::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:mc.comm.PBShaderProgram)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string vs = 1;
  if (!this->_internal_vs().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_vs().data(), static_cast<int>(this->_internal_vs().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "mc.comm.PBShaderProgram.vs");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_vs(), target);
  }

  // string fs = 2;
  if (!this->_internal_fs().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_fs().data(), static_cast<int>(this->_internal_fs().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "mc.comm.PBShaderProgram.fs");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_fs(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:mc.comm.PBShaderProgram)
  return target;
}

size_t PBShaderProgram::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:mc.comm.PBShaderProgram)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string vs = 1;
  if (!this->_internal_vs().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_vs());
  }

  // string fs = 2;
  if (!this->_internal_fs().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_fs());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData PBShaderProgram::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    PBShaderProgram::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*PBShaderProgram::GetClassData() const { return &_class_data_; }


void PBShaderProgram::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<PBShaderProgram*>(&to_msg);
  auto& from = static_cast<const PBShaderProgram&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:mc.comm.PBShaderProgram)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_vs().empty()) {
    _this->_internal_set_vs(from._internal_vs());
  }
  if (!from._internal_fs().empty()) {
    _this->_internal_set_fs(from._internal_fs());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void PBShaderProgram::CopyFrom(const PBShaderProgram& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:mc.comm.PBShaderProgram)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PBShaderProgram::IsInitialized() const {
  return true;
}

void PBShaderProgram::InternalSwap(PBShaderProgram* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.vs_, lhs_arena,
      &other->_impl_.vs_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.fs_, lhs_arena,
      &other->_impl_.fs_, rhs_arena
  );
}

::PROTOBUF_NAMESPACE_ID::Metadata PBShaderProgram::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_mc_2fcomm_2fpbshaderprogram_2eproto_getter, &descriptor_table_mc_2fcomm_2fpbshaderprogram_2eproto_once,
      file_level_metadata_mc_2fcomm_2fpbshaderprogram_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace comm
}  // namespace mc
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::mc::comm::PBShaderProgram*
Arena::CreateMaybeMessage< ::mc::comm::PBShaderProgram >(Arena* arena) {
  return Arena::CreateMessageInternal< ::mc::comm::PBShaderProgram >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>