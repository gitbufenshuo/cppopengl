// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: mc/comm/pbmodel.proto

#include "mc/comm/pbmodel.pb.h"

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
PROTOBUF_CONSTEXPR PBModel::PBModel(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.attrib_)*/{}
  , /*decltype(_impl_._attrib_cached_byte_size_)*/{0}
  , /*decltype(_impl_.bin_buffer_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.begin_)*/0
  , /*decltype(_impl_.length_)*/0
  , /*decltype(_impl_.ebo_length_)*/0
  , /*decltype(_impl_.ebo_type_)*/0
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct PBModelDefaultTypeInternal {
  PROTOBUF_CONSTEXPR PBModelDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~PBModelDefaultTypeInternal() {}
  union {
    PBModel _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 PBModelDefaultTypeInternal _PBModel_default_instance_;
}  // namespace comm
}  // namespace mc
static ::_pb::Metadata file_level_metadata_mc_2fcomm_2fpbmodel_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_mc_2fcomm_2fpbmodel_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_mc_2fcomm_2fpbmodel_2eproto = nullptr;

const uint32_t TableStruct_mc_2fcomm_2fpbmodel_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBModel, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBModel, _impl_.bin_buffer_),
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBModel, _impl_.begin_),
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBModel, _impl_.length_),
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBModel, _impl_.ebo_length_),
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBModel, _impl_.ebo_type_),
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBModel, _impl_.attrib_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::mc::comm::PBModel)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::mc::comm::_PBModel_default_instance_._instance,
};

const char descriptor_table_protodef_mc_2fcomm_2fpbmodel_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\025mc/comm/pbmodel.proto\022\007mc.comm\"r\n\007PBMo"
  "del\022\022\n\nbin_buffer\030\001 \001(\t\022\r\n\005begin\030\002 \001(\005\022\016"
  "\n\006length\030\003 \001(\005\022\022\n\nebo_length\030\004 \001(\005\022\020\n\010eb"
  "o_type\030\005 \001(\005\022\016\n\006attrib\030\006 \003(\005B\tZ\007mc/commb"
  "\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_mc_2fcomm_2fpbmodel_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_mc_2fcomm_2fpbmodel_2eproto = {
    false, false, 167, descriptor_table_protodef_mc_2fcomm_2fpbmodel_2eproto,
    "mc/comm/pbmodel.proto",
    &descriptor_table_mc_2fcomm_2fpbmodel_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_mc_2fcomm_2fpbmodel_2eproto::offsets,
    file_level_metadata_mc_2fcomm_2fpbmodel_2eproto, file_level_enum_descriptors_mc_2fcomm_2fpbmodel_2eproto,
    file_level_service_descriptors_mc_2fcomm_2fpbmodel_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_mc_2fcomm_2fpbmodel_2eproto_getter() {
  return &descriptor_table_mc_2fcomm_2fpbmodel_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_mc_2fcomm_2fpbmodel_2eproto(&descriptor_table_mc_2fcomm_2fpbmodel_2eproto);
namespace mc {
namespace comm {

// ===================================================================

class PBModel::_Internal {
 public:
};

PBModel::PBModel(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:mc.comm.PBModel)
}
PBModel::PBModel(const PBModel& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  PBModel* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.attrib_){from._impl_.attrib_}
    , /*decltype(_impl_._attrib_cached_byte_size_)*/{0}
    , decltype(_impl_.bin_buffer_){}
    , decltype(_impl_.begin_){}
    , decltype(_impl_.length_){}
    , decltype(_impl_.ebo_length_){}
    , decltype(_impl_.ebo_type_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.bin_buffer_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.bin_buffer_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_bin_buffer().empty()) {
    _this->_impl_.bin_buffer_.Set(from._internal_bin_buffer(), 
      _this->GetArenaForAllocation());
  }
  ::memcpy(&_impl_.begin_, &from._impl_.begin_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.ebo_type_) -
    reinterpret_cast<char*>(&_impl_.begin_)) + sizeof(_impl_.ebo_type_));
  // @@protoc_insertion_point(copy_constructor:mc.comm.PBModel)
}

inline void PBModel::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.attrib_){arena}
    , /*decltype(_impl_._attrib_cached_byte_size_)*/{0}
    , decltype(_impl_.bin_buffer_){}
    , decltype(_impl_.begin_){0}
    , decltype(_impl_.length_){0}
    , decltype(_impl_.ebo_length_){0}
    , decltype(_impl_.ebo_type_){0}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.bin_buffer_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.bin_buffer_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

PBModel::~PBModel() {
  // @@protoc_insertion_point(destructor:mc.comm.PBModel)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void PBModel::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.attrib_.~RepeatedField();
  _impl_.bin_buffer_.Destroy();
}

void PBModel::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void PBModel::Clear() {
// @@protoc_insertion_point(message_clear_start:mc.comm.PBModel)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.attrib_.Clear();
  _impl_.bin_buffer_.ClearToEmpty();
  ::memset(&_impl_.begin_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.ebo_type_) -
      reinterpret_cast<char*>(&_impl_.begin_)) + sizeof(_impl_.ebo_type_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* PBModel::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string bin_buffer = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_bin_buffer();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "mc.comm.PBModel.bin_buffer"));
        } else
          goto handle_unusual;
        continue;
      // int32 begin = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          _impl_.begin_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int32 length = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 24)) {
          _impl_.length_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int32 ebo_length = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 32)) {
          _impl_.ebo_length_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int32 ebo_type = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 40)) {
          _impl_.ebo_type_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // repeated int32 attrib = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 50)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedInt32Parser(_internal_mutable_attrib(), ptr, ctx);
          CHK_(ptr);
        } else if (static_cast<uint8_t>(tag) == 48) {
          _internal_add_attrib(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr));
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

uint8_t* PBModel::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:mc.comm.PBModel)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string bin_buffer = 1;
  if (!this->_internal_bin_buffer().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_bin_buffer().data(), static_cast<int>(this->_internal_bin_buffer().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "mc.comm.PBModel.bin_buffer");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_bin_buffer(), target);
  }

  // int32 begin = 2;
  if (this->_internal_begin() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(2, this->_internal_begin(), target);
  }

  // int32 length = 3;
  if (this->_internal_length() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(3, this->_internal_length(), target);
  }

  // int32 ebo_length = 4;
  if (this->_internal_ebo_length() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(4, this->_internal_ebo_length(), target);
  }

  // int32 ebo_type = 5;
  if (this->_internal_ebo_type() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(5, this->_internal_ebo_type(), target);
  }

  // repeated int32 attrib = 6;
  {
    int byte_size = _impl_._attrib_cached_byte_size_.load(std::memory_order_relaxed);
    if (byte_size > 0) {
      target = stream->WriteInt32Packed(
          6, _internal_attrib(), byte_size, target);
    }
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:mc.comm.PBModel)
  return target;
}

size_t PBModel::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:mc.comm.PBModel)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated int32 attrib = 6;
  {
    size_t data_size = ::_pbi::WireFormatLite::
      Int32Size(this->_impl_.attrib_);
    if (data_size > 0) {
      total_size += 1 +
        ::_pbi::WireFormatLite::Int32Size(static_cast<int32_t>(data_size));
    }
    int cached_size = ::_pbi::ToCachedSize(data_size);
    _impl_._attrib_cached_byte_size_.store(cached_size,
                                    std::memory_order_relaxed);
    total_size += data_size;
  }

  // string bin_buffer = 1;
  if (!this->_internal_bin_buffer().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_bin_buffer());
  }

  // int32 begin = 2;
  if (this->_internal_begin() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_begin());
  }

  // int32 length = 3;
  if (this->_internal_length() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_length());
  }

  // int32 ebo_length = 4;
  if (this->_internal_ebo_length() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_ebo_length());
  }

  // int32 ebo_type = 5;
  if (this->_internal_ebo_type() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_ebo_type());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData PBModel::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    PBModel::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*PBModel::GetClassData() const { return &_class_data_; }


void PBModel::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<PBModel*>(&to_msg);
  auto& from = static_cast<const PBModel&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:mc.comm.PBModel)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_impl_.attrib_.MergeFrom(from._impl_.attrib_);
  if (!from._internal_bin_buffer().empty()) {
    _this->_internal_set_bin_buffer(from._internal_bin_buffer());
  }
  if (from._internal_begin() != 0) {
    _this->_internal_set_begin(from._internal_begin());
  }
  if (from._internal_length() != 0) {
    _this->_internal_set_length(from._internal_length());
  }
  if (from._internal_ebo_length() != 0) {
    _this->_internal_set_ebo_length(from._internal_ebo_length());
  }
  if (from._internal_ebo_type() != 0) {
    _this->_internal_set_ebo_type(from._internal_ebo_type());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void PBModel::CopyFrom(const PBModel& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:mc.comm.PBModel)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PBModel::IsInitialized() const {
  return true;
}

void PBModel::InternalSwap(PBModel* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  _impl_.attrib_.InternalSwap(&other->_impl_.attrib_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.bin_buffer_, lhs_arena,
      &other->_impl_.bin_buffer_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(PBModel, _impl_.ebo_type_)
      + sizeof(PBModel::_impl_.ebo_type_)
      - PROTOBUF_FIELD_OFFSET(PBModel, _impl_.begin_)>(
          reinterpret_cast<char*>(&_impl_.begin_),
          reinterpret_cast<char*>(&other->_impl_.begin_));
}

::PROTOBUF_NAMESPACE_ID::Metadata PBModel::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_mc_2fcomm_2fpbmodel_2eproto_getter, &descriptor_table_mc_2fcomm_2fpbmodel_2eproto_once,
      file_level_metadata_mc_2fcomm_2fpbmodel_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace comm
}  // namespace mc
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::mc::comm::PBModel*
Arena::CreateMaybeMessage< ::mc::comm::PBModel >(Arena* arena) {
  return Arena::CreateMessageInternal< ::mc::comm::PBModel >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
