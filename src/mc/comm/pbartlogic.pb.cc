// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: mc/comm/pbartlogic.proto

#include "mc/comm/pbartlogic.pb.h"

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
PROTOBUF_CONSTEXPR PBArtLogic::PBArtLogic(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.logic_class_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.properties_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct PBArtLogicDefaultTypeInternal {
  PROTOBUF_CONSTEXPR PBArtLogicDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~PBArtLogicDefaultTypeInternal() {}
  union {
    PBArtLogic _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 PBArtLogicDefaultTypeInternal _PBArtLogic_default_instance_;
}  // namespace comm
}  // namespace mc
static ::_pb::Metadata file_level_metadata_mc_2fcomm_2fpbartlogic_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_mc_2fcomm_2fpbartlogic_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_mc_2fcomm_2fpbartlogic_2eproto = nullptr;

const uint32_t TableStruct_mc_2fcomm_2fpbartlogic_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBArtLogic, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBArtLogic, _impl_.logic_class_),
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBArtLogic, _impl_.properties_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::mc::comm::PBArtLogic)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::mc::comm::_PBArtLogic_default_instance_._instance,
};

const char descriptor_table_protodef_mc_2fcomm_2fpbartlogic_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\030mc/comm/pbartlogic.proto\022\007mc.comm\"5\n\nP"
  "BArtLogic\022\023\n\013logic_class\030\001 \001(\t\022\022\n\nproper"
  "ties\030\002 \001(\tB\tZ\007mc/commb\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_mc_2fcomm_2fpbartlogic_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_mc_2fcomm_2fpbartlogic_2eproto = {
    false, false, 109, descriptor_table_protodef_mc_2fcomm_2fpbartlogic_2eproto,
    "mc/comm/pbartlogic.proto",
    &descriptor_table_mc_2fcomm_2fpbartlogic_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_mc_2fcomm_2fpbartlogic_2eproto::offsets,
    file_level_metadata_mc_2fcomm_2fpbartlogic_2eproto, file_level_enum_descriptors_mc_2fcomm_2fpbartlogic_2eproto,
    file_level_service_descriptors_mc_2fcomm_2fpbartlogic_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_mc_2fcomm_2fpbartlogic_2eproto_getter() {
  return &descriptor_table_mc_2fcomm_2fpbartlogic_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_mc_2fcomm_2fpbartlogic_2eproto(&descriptor_table_mc_2fcomm_2fpbartlogic_2eproto);
namespace mc {
namespace comm {

// ===================================================================

class PBArtLogic::_Internal {
 public:
};

PBArtLogic::PBArtLogic(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:mc.comm.PBArtLogic)
}
PBArtLogic::PBArtLogic(const PBArtLogic& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  PBArtLogic* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.logic_class_){}
    , decltype(_impl_.properties_){}
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
  _impl_.properties_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.properties_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_properties().empty()) {
    _this->_impl_.properties_.Set(from._internal_properties(), 
      _this->GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:mc.comm.PBArtLogic)
}

inline void PBArtLogic::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.logic_class_){}
    , decltype(_impl_.properties_){}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.logic_class_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.logic_class_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.properties_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.properties_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

PBArtLogic::~PBArtLogic() {
  // @@protoc_insertion_point(destructor:mc.comm.PBArtLogic)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void PBArtLogic::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.logic_class_.Destroy();
  _impl_.properties_.Destroy();
}

void PBArtLogic::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void PBArtLogic::Clear() {
// @@protoc_insertion_point(message_clear_start:mc.comm.PBArtLogic)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.logic_class_.ClearToEmpty();
  _impl_.properties_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* PBArtLogic::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
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
          CHK_(::_pbi::VerifyUTF8(str, "mc.comm.PBArtLogic.logic_class"));
        } else
          goto handle_unusual;
        continue;
      // string properties = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_properties();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "mc.comm.PBArtLogic.properties"));
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

uint8_t* PBArtLogic::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:mc.comm.PBArtLogic)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string logic_class = 1;
  if (!this->_internal_logic_class().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_logic_class().data(), static_cast<int>(this->_internal_logic_class().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "mc.comm.PBArtLogic.logic_class");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_logic_class(), target);
  }

  // string properties = 2;
  if (!this->_internal_properties().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_properties().data(), static_cast<int>(this->_internal_properties().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "mc.comm.PBArtLogic.properties");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_properties(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:mc.comm.PBArtLogic)
  return target;
}

size_t PBArtLogic::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:mc.comm.PBArtLogic)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string logic_class = 1;
  if (!this->_internal_logic_class().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_logic_class());
  }

  // string properties = 2;
  if (!this->_internal_properties().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_properties());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData PBArtLogic::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    PBArtLogic::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*PBArtLogic::GetClassData() const { return &_class_data_; }


void PBArtLogic::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<PBArtLogic*>(&to_msg);
  auto& from = static_cast<const PBArtLogic&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:mc.comm.PBArtLogic)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_logic_class().empty()) {
    _this->_internal_set_logic_class(from._internal_logic_class());
  }
  if (!from._internal_properties().empty()) {
    _this->_internal_set_properties(from._internal_properties());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void PBArtLogic::CopyFrom(const PBArtLogic& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:mc.comm.PBArtLogic)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PBArtLogic::IsInitialized() const {
  return true;
}

void PBArtLogic::InternalSwap(PBArtLogic* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.logic_class_, lhs_arena,
      &other->_impl_.logic_class_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.properties_, lhs_arena,
      &other->_impl_.properties_, rhs_arena
  );
}

::PROTOBUF_NAMESPACE_ID::Metadata PBArtLogic::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_mc_2fcomm_2fpbartlogic_2eproto_getter, &descriptor_table_mc_2fcomm_2fpbartlogic_2eproto_once,
      file_level_metadata_mc_2fcomm_2fpbartlogic_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace comm
}  // namespace mc
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::mc::comm::PBArtLogic*
Arena::CreateMaybeMessage< ::mc::comm::PBArtLogic >(Arena* arena) {
  return Arena::CreateMessageInternal< ::mc::comm::PBArtLogic >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
