// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: mc/comm/pbmaterial.proto

#include "mc/comm/pbmaterial.pb.h"

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
PROTOBUF_CONSTEXPR PBMaterial::PBMaterial(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.texture_list_)*/{}
  , /*decltype(_impl_.logic_class_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.shader_program_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct PBMaterialDefaultTypeInternal {
  PROTOBUF_CONSTEXPR PBMaterialDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~PBMaterialDefaultTypeInternal() {}
  union {
    PBMaterial _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 PBMaterialDefaultTypeInternal _PBMaterial_default_instance_;
}  // namespace comm
}  // namespace mc
static ::_pb::Metadata file_level_metadata_mc_2fcomm_2fpbmaterial_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_mc_2fcomm_2fpbmaterial_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_mc_2fcomm_2fpbmaterial_2eproto = nullptr;

const uint32_t TableStruct_mc_2fcomm_2fpbmaterial_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBMaterial, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBMaterial, _impl_.logic_class_),
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBMaterial, _impl_.texture_list_),
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBMaterial, _impl_.shader_program_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::mc::comm::PBMaterial)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::mc::comm::_PBMaterial_default_instance_._instance,
};

const char descriptor_table_protodef_mc_2fcomm_2fpbmaterial_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\030mc/comm/pbmaterial.proto\022\007mc.comm\"O\n\nP"
  "BMaterial\022\023\n\013logic_class\030\001 \001(\t\022\024\n\014textur"
  "e_list\030\002 \003(\t\022\026\n\016shader_program\030\003 \001(\tB\tZ\007"
  "mc/commb\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_mc_2fcomm_2fpbmaterial_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_mc_2fcomm_2fpbmaterial_2eproto = {
    false, false, 135, descriptor_table_protodef_mc_2fcomm_2fpbmaterial_2eproto,
    "mc/comm/pbmaterial.proto",
    &descriptor_table_mc_2fcomm_2fpbmaterial_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_mc_2fcomm_2fpbmaterial_2eproto::offsets,
    file_level_metadata_mc_2fcomm_2fpbmaterial_2eproto, file_level_enum_descriptors_mc_2fcomm_2fpbmaterial_2eproto,
    file_level_service_descriptors_mc_2fcomm_2fpbmaterial_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_mc_2fcomm_2fpbmaterial_2eproto_getter() {
  return &descriptor_table_mc_2fcomm_2fpbmaterial_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_mc_2fcomm_2fpbmaterial_2eproto(&descriptor_table_mc_2fcomm_2fpbmaterial_2eproto);
namespace mc {
namespace comm {

// ===================================================================

class PBMaterial::_Internal {
 public:
};

PBMaterial::PBMaterial(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:mc.comm.PBMaterial)
}
PBMaterial::PBMaterial(const PBMaterial& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  PBMaterial* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.texture_list_){from._impl_.texture_list_}
    , decltype(_impl_.logic_class_){}
    , decltype(_impl_.shader_program_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.logic_class_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.logic_class_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_logic_class().empty()) {
    _this->_impl_.logic_class_.Set(from._internal_logic_class(), 
      _this->GetArenaForAllocation());
  }
  _impl_.shader_program_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.shader_program_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_shader_program().empty()) {
    _this->_impl_.shader_program_.Set(from._internal_shader_program(), 
      _this->GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:mc.comm.PBMaterial)
}

inline void PBMaterial::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.texture_list_){arena}
    , decltype(_impl_.logic_class_){}
    , decltype(_impl_.shader_program_){}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.logic_class_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.logic_class_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.shader_program_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.shader_program_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

PBMaterial::~PBMaterial() {
  // @@protoc_insertion_point(destructor:mc.comm.PBMaterial)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void PBMaterial::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.texture_list_.~RepeatedPtrField();
  _impl_.logic_class_.Destroy();
  _impl_.shader_program_.Destroy();
}

void PBMaterial::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void PBMaterial::Clear() {
// @@protoc_insertion_point(message_clear_start:mc.comm.PBMaterial)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.texture_list_.Clear();
  _impl_.logic_class_.ClearToEmpty();
  _impl_.shader_program_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* PBMaterial::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string logic_class = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_logic_class();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "mc.comm.PBMaterial.logic_class"));
        } else
          goto handle_unusual;
        continue;
      // repeated string texture_list = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          ptr -= 1;
          do {
            ptr += 1;
            auto str = _internal_add_texture_list();
            ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
            CHK_(ptr);
            CHK_(::_pbi::VerifyUTF8(str, "mc.comm.PBMaterial.texture_list"));
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<18>(ptr));
        } else
          goto handle_unusual;
        continue;
      // string shader_program = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 26)) {
          auto str = _internal_mutable_shader_program();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "mc.comm.PBMaterial.shader_program"));
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

uint8_t* PBMaterial::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:mc.comm.PBMaterial)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string logic_class = 1;
  if (!this->_internal_logic_class().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_logic_class().data(), static_cast<int>(this->_internal_logic_class().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "mc.comm.PBMaterial.logic_class");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_logic_class(), target);
  }

  // repeated string texture_list = 2;
  for (int i = 0, n = this->_internal_texture_list_size(); i < n; i++) {
    const auto& s = this->_internal_texture_list(i);
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      s.data(), static_cast<int>(s.length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "mc.comm.PBMaterial.texture_list");
    target = stream->WriteString(2, s, target);
  }

  // string shader_program = 3;
  if (!this->_internal_shader_program().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_shader_program().data(), static_cast<int>(this->_internal_shader_program().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "mc.comm.PBMaterial.shader_program");
    target = stream->WriteStringMaybeAliased(
        3, this->_internal_shader_program(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:mc.comm.PBMaterial)
  return target;
}

size_t PBMaterial::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:mc.comm.PBMaterial)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated string texture_list = 2;
  total_size += 1 *
      ::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(_impl_.texture_list_.size());
  for (int i = 0, n = _impl_.texture_list_.size(); i < n; i++) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
      _impl_.texture_list_.Get(i));
  }

  // string logic_class = 1;
  if (!this->_internal_logic_class().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_logic_class());
  }

  // string shader_program = 3;
  if (!this->_internal_shader_program().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_shader_program());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData PBMaterial::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    PBMaterial::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*PBMaterial::GetClassData() const { return &_class_data_; }


void PBMaterial::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<PBMaterial*>(&to_msg);
  auto& from = static_cast<const PBMaterial&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:mc.comm.PBMaterial)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_impl_.texture_list_.MergeFrom(from._impl_.texture_list_);
  if (!from._internal_logic_class().empty()) {
    _this->_internal_set_logic_class(from._internal_logic_class());
  }
  if (!from._internal_shader_program().empty()) {
    _this->_internal_set_shader_program(from._internal_shader_program());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void PBMaterial::CopyFrom(const PBMaterial& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:mc.comm.PBMaterial)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PBMaterial::IsInitialized() const {
  return true;
}

void PBMaterial::InternalSwap(PBMaterial* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  _impl_.texture_list_.InternalSwap(&other->_impl_.texture_list_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.logic_class_, lhs_arena,
      &other->_impl_.logic_class_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.shader_program_, lhs_arena,
      &other->_impl_.shader_program_, rhs_arena
  );
}

::PROTOBUF_NAMESPACE_ID::Metadata PBMaterial::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_mc_2fcomm_2fpbmaterial_2eproto_getter, &descriptor_table_mc_2fcomm_2fpbmaterial_2eproto_once,
      file_level_metadata_mc_2fcomm_2fpbmaterial_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace comm
}  // namespace mc
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::mc::comm::PBMaterial*
Arena::CreateMaybeMessage< ::mc::comm::PBMaterial >(Arena* arena) {
  return Arena::CreateMessageInternal< ::mc::comm::PBMaterial >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
