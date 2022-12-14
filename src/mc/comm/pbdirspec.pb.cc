// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: mc/comm/pbdirspec.proto

#include "mc/comm/pbdirspec.pb.h"

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
PROTOBUF_CONSTEXPR PBDirSpec::PBDirSpec(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.image_list_)*/{}
  , /*decltype(_impl_.bin_buffer_list_)*/{}
  , /*decltype(_impl_.shader_code_list_)*/{}
  , /*decltype(_impl_.art_logic_list_)*/{}
  , /*decltype(_impl_.act_logic_list_)*/{}
  , /*decltype(_impl_.texture_list_)*/{}
  , /*decltype(_impl_.model_list_)*/{}
  , /*decltype(_impl_.shader_program_list_)*/{}
  , /*decltype(_impl_.material_list_)*/{}
  , /*decltype(_impl_.scene_list_)*/{}
  , /*decltype(_impl_.node_list_)*/{}
  , /*decltype(_impl_.light_list_)*/{}
  , /*decltype(_impl_.base_dir_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct PBDirSpecDefaultTypeInternal {
  PROTOBUF_CONSTEXPR PBDirSpecDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~PBDirSpecDefaultTypeInternal() {}
  union {
    PBDirSpec _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 PBDirSpecDefaultTypeInternal _PBDirSpec_default_instance_;
}  // namespace comm
}  // namespace mc
static ::_pb::Metadata file_level_metadata_mc_2fcomm_2fpbdirspec_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_mc_2fcomm_2fpbdirspec_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_mc_2fcomm_2fpbdirspec_2eproto = nullptr;

const uint32_t TableStruct_mc_2fcomm_2fpbdirspec_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBDirSpec, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBDirSpec, _impl_.base_dir_),
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBDirSpec, _impl_.image_list_),
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBDirSpec, _impl_.bin_buffer_list_),
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBDirSpec, _impl_.shader_code_list_),
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBDirSpec, _impl_.art_logic_list_),
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBDirSpec, _impl_.act_logic_list_),
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBDirSpec, _impl_.texture_list_),
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBDirSpec, _impl_.model_list_),
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBDirSpec, _impl_.shader_program_list_),
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBDirSpec, _impl_.material_list_),
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBDirSpec, _impl_.scene_list_),
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBDirSpec, _impl_.node_list_),
  PROTOBUF_FIELD_OFFSET(::mc::comm::PBDirSpec, _impl_.light_list_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::mc::comm::PBDirSpec)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::mc::comm::_PBDirSpec_default_instance_._instance,
};

const char descriptor_table_protodef_mc_2fcomm_2fpbdirspec_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\027mc/comm/pbdirspec.proto\022\007mc.comm\"\255\002\n\tP"
  "BDirSpec\022\020\n\010base_dir\030\001 \001(\t\022\022\n\nimage_list"
  "\030\002 \003(\t\022\027\n\017bin_buffer_list\030\003 \003(\t\022\030\n\020shade"
  "r_code_list\030\004 \003(\t\022\026\n\016art_logic_list\030\005 \003("
  "\t\022\026\n\016act_logic_list\030\006 \003(\t\022\024\n\014texture_lis"
  "t\030\007 \003(\t\022\022\n\nmodel_list\030\010 \003(\t\022\033\n\023shader_pr"
  "ogram_list\030\t \003(\t\022\025\n\rmaterial_list\030\n \003(\t\022"
  "\022\n\nscene_list\030\013 \003(\t\022\021\n\tnode_list\030\014 \003(\t\022\022"
  "\n\nlight_list\030\r \003(\tB\tZ\007mc/commb\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_mc_2fcomm_2fpbdirspec_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_mc_2fcomm_2fpbdirspec_2eproto = {
    false, false, 357, descriptor_table_protodef_mc_2fcomm_2fpbdirspec_2eproto,
    "mc/comm/pbdirspec.proto",
    &descriptor_table_mc_2fcomm_2fpbdirspec_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_mc_2fcomm_2fpbdirspec_2eproto::offsets,
    file_level_metadata_mc_2fcomm_2fpbdirspec_2eproto, file_level_enum_descriptors_mc_2fcomm_2fpbdirspec_2eproto,
    file_level_service_descriptors_mc_2fcomm_2fpbdirspec_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_mc_2fcomm_2fpbdirspec_2eproto_getter() {
  return &descriptor_table_mc_2fcomm_2fpbdirspec_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_mc_2fcomm_2fpbdirspec_2eproto(&descriptor_table_mc_2fcomm_2fpbdirspec_2eproto);
namespace mc {
namespace comm {

// ===================================================================

class PBDirSpec::_Internal {
 public:
};

PBDirSpec::PBDirSpec(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:mc.comm.PBDirSpec)
}
PBDirSpec::PBDirSpec(const PBDirSpec& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  PBDirSpec* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.image_list_){from._impl_.image_list_}
    , decltype(_impl_.bin_buffer_list_){from._impl_.bin_buffer_list_}
    , decltype(_impl_.shader_code_list_){from._impl_.shader_code_list_}
    , decltype(_impl_.art_logic_list_){from._impl_.art_logic_list_}
    , decltype(_impl_.act_logic_list_){from._impl_.act_logic_list_}
    , decltype(_impl_.texture_list_){from._impl_.texture_list_}
    , decltype(_impl_.model_list_){from._impl_.model_list_}
    , decltype(_impl_.shader_program_list_){from._impl_.shader_program_list_}
    , decltype(_impl_.material_list_){from._impl_.material_list_}
    , decltype(_impl_.scene_list_){from._impl_.scene_list_}
    , decltype(_impl_.node_list_){from._impl_.node_list_}
    , decltype(_impl_.light_list_){from._impl_.light_list_}
    , decltype(_impl_.base_dir_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.base_dir_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.base_dir_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_base_dir().empty()) {
    _this->_impl_.base_dir_.Set(from._internal_base_dir(), 
      _this->GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:mc.comm.PBDirSpec)
}

inline void PBDirSpec::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.image_list_){arena}
    , decltype(_impl_.bin_buffer_list_){arena}
    , decltype(_impl_.shader_code_list_){arena}
    , decltype(_impl_.art_logic_list_){arena}
    , decltype(_impl_.act_logic_list_){arena}
    , decltype(_impl_.texture_list_){arena}
    , decltype(_impl_.model_list_){arena}
    , decltype(_impl_.shader_program_list_){arena}
    , decltype(_impl_.material_list_){arena}
    , decltype(_impl_.scene_list_){arena}
    , decltype(_impl_.node_list_){arena}
    , decltype(_impl_.light_list_){arena}
    , decltype(_impl_.base_dir_){}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.base_dir_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.base_dir_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

PBDirSpec::~PBDirSpec() {
  // @@protoc_insertion_point(destructor:mc.comm.PBDirSpec)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void PBDirSpec::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.image_list_.~RepeatedPtrField();
  _impl_.bin_buffer_list_.~RepeatedPtrField();
  _impl_.shader_code_list_.~RepeatedPtrField();
  _impl_.art_logic_list_.~RepeatedPtrField();
  _impl_.act_logic_list_.~RepeatedPtrField();
  _impl_.texture_list_.~RepeatedPtrField();
  _impl_.model_list_.~RepeatedPtrField();
  _impl_.shader_program_list_.~RepeatedPtrField();
  _impl_.material_list_.~RepeatedPtrField();
  _impl_.scene_list_.~RepeatedPtrField();
  _impl_.node_list_.~RepeatedPtrField();
  _impl_.light_list_.~RepeatedPtrField();
  _impl_.base_dir_.Destroy();
}

void PBDirSpec::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void PBDirSpec::Clear() {
// @@protoc_insertion_point(message_clear_start:mc.comm.PBDirSpec)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.image_list_.Clear();
  _impl_.bin_buffer_list_.Clear();
  _impl_.shader_code_list_.Clear();
  _impl_.art_logic_list_.Clear();
  _impl_.act_logic_list_.Clear();
  _impl_.texture_list_.Clear();
  _impl_.model_list_.Clear();
  _impl_.shader_program_list_.Clear();
  _impl_.material_list_.Clear();
  _impl_.scene_list_.Clear();
  _impl_.node_list_.Clear();
  _impl_.light_list_.Clear();
  _impl_.base_dir_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* PBDirSpec::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string base_dir = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_base_dir();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "mc.comm.PBDirSpec.base_dir"));
        } else
          goto handle_unusual;
        continue;
      // repeated string image_list = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          ptr -= 1;
          do {
            ptr += 1;
            auto str = _internal_add_image_list();
            ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
            CHK_(ptr);
            CHK_(::_pbi::VerifyUTF8(str, "mc.comm.PBDirSpec.image_list"));
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<18>(ptr));
        } else
          goto handle_unusual;
        continue;
      // repeated string bin_buffer_list = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 26)) {
          ptr -= 1;
          do {
            ptr += 1;
            auto str = _internal_add_bin_buffer_list();
            ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
            CHK_(ptr);
            CHK_(::_pbi::VerifyUTF8(str, "mc.comm.PBDirSpec.bin_buffer_list"));
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<26>(ptr));
        } else
          goto handle_unusual;
        continue;
      // repeated string shader_code_list = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 34)) {
          ptr -= 1;
          do {
            ptr += 1;
            auto str = _internal_add_shader_code_list();
            ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
            CHK_(ptr);
            CHK_(::_pbi::VerifyUTF8(str, "mc.comm.PBDirSpec.shader_code_list"));
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<34>(ptr));
        } else
          goto handle_unusual;
        continue;
      // repeated string art_logic_list = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 42)) {
          ptr -= 1;
          do {
            ptr += 1;
            auto str = _internal_add_art_logic_list();
            ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
            CHK_(ptr);
            CHK_(::_pbi::VerifyUTF8(str, "mc.comm.PBDirSpec.art_logic_list"));
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<42>(ptr));
        } else
          goto handle_unusual;
        continue;
      // repeated string act_logic_list = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 50)) {
          ptr -= 1;
          do {
            ptr += 1;
            auto str = _internal_add_act_logic_list();
            ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
            CHK_(ptr);
            CHK_(::_pbi::VerifyUTF8(str, "mc.comm.PBDirSpec.act_logic_list"));
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<50>(ptr));
        } else
          goto handle_unusual;
        continue;
      // repeated string texture_list = 7;
      case 7:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 58)) {
          ptr -= 1;
          do {
            ptr += 1;
            auto str = _internal_add_texture_list();
            ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
            CHK_(ptr);
            CHK_(::_pbi::VerifyUTF8(str, "mc.comm.PBDirSpec.texture_list"));
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<58>(ptr));
        } else
          goto handle_unusual;
        continue;
      // repeated string model_list = 8;
      case 8:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 66)) {
          ptr -= 1;
          do {
            ptr += 1;
            auto str = _internal_add_model_list();
            ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
            CHK_(ptr);
            CHK_(::_pbi::VerifyUTF8(str, "mc.comm.PBDirSpec.model_list"));
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<66>(ptr));
        } else
          goto handle_unusual;
        continue;
      // repeated string shader_program_list = 9;
      case 9:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 74)) {
          ptr -= 1;
          do {
            ptr += 1;
            auto str = _internal_add_shader_program_list();
            ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
            CHK_(ptr);
            CHK_(::_pbi::VerifyUTF8(str, "mc.comm.PBDirSpec.shader_program_list"));
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<74>(ptr));
        } else
          goto handle_unusual;
        continue;
      // repeated string material_list = 10;
      case 10:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 82)) {
          ptr -= 1;
          do {
            ptr += 1;
            auto str = _internal_add_material_list();
            ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
            CHK_(ptr);
            CHK_(::_pbi::VerifyUTF8(str, "mc.comm.PBDirSpec.material_list"));
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<82>(ptr));
        } else
          goto handle_unusual;
        continue;
      // repeated string scene_list = 11;
      case 11:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 90)) {
          ptr -= 1;
          do {
            ptr += 1;
            auto str = _internal_add_scene_list();
            ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
            CHK_(ptr);
            CHK_(::_pbi::VerifyUTF8(str, "mc.comm.PBDirSpec.scene_list"));
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<90>(ptr));
        } else
          goto handle_unusual;
        continue;
      // repeated string node_list = 12;
      case 12:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 98)) {
          ptr -= 1;
          do {
            ptr += 1;
            auto str = _internal_add_node_list();
            ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
            CHK_(ptr);
            CHK_(::_pbi::VerifyUTF8(str, "mc.comm.PBDirSpec.node_list"));
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<98>(ptr));
        } else
          goto handle_unusual;
        continue;
      // repeated string light_list = 13;
      case 13:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 106)) {
          ptr -= 1;
          do {
            ptr += 1;
            auto str = _internal_add_light_list();
            ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
            CHK_(ptr);
            CHK_(::_pbi::VerifyUTF8(str, "mc.comm.PBDirSpec.light_list"));
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<106>(ptr));
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

uint8_t* PBDirSpec::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:mc.comm.PBDirSpec)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string base_dir = 1;
  if (!this->_internal_base_dir().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_base_dir().data(), static_cast<int>(this->_internal_base_dir().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "mc.comm.PBDirSpec.base_dir");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_base_dir(), target);
  }

  // repeated string image_list = 2;
  for (int i = 0, n = this->_internal_image_list_size(); i < n; i++) {
    const auto& s = this->_internal_image_list(i);
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      s.data(), static_cast<int>(s.length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "mc.comm.PBDirSpec.image_list");
    target = stream->WriteString(2, s, target);
  }

  // repeated string bin_buffer_list = 3;
  for (int i = 0, n = this->_internal_bin_buffer_list_size(); i < n; i++) {
    const auto& s = this->_internal_bin_buffer_list(i);
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      s.data(), static_cast<int>(s.length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "mc.comm.PBDirSpec.bin_buffer_list");
    target = stream->WriteString(3, s, target);
  }

  // repeated string shader_code_list = 4;
  for (int i = 0, n = this->_internal_shader_code_list_size(); i < n; i++) {
    const auto& s = this->_internal_shader_code_list(i);
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      s.data(), static_cast<int>(s.length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "mc.comm.PBDirSpec.shader_code_list");
    target = stream->WriteString(4, s, target);
  }

  // repeated string art_logic_list = 5;
  for (int i = 0, n = this->_internal_art_logic_list_size(); i < n; i++) {
    const auto& s = this->_internal_art_logic_list(i);
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      s.data(), static_cast<int>(s.length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "mc.comm.PBDirSpec.art_logic_list");
    target = stream->WriteString(5, s, target);
  }

  // repeated string act_logic_list = 6;
  for (int i = 0, n = this->_internal_act_logic_list_size(); i < n; i++) {
    const auto& s = this->_internal_act_logic_list(i);
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      s.data(), static_cast<int>(s.length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "mc.comm.PBDirSpec.act_logic_list");
    target = stream->WriteString(6, s, target);
  }

  // repeated string texture_list = 7;
  for (int i = 0, n = this->_internal_texture_list_size(); i < n; i++) {
    const auto& s = this->_internal_texture_list(i);
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      s.data(), static_cast<int>(s.length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "mc.comm.PBDirSpec.texture_list");
    target = stream->WriteString(7, s, target);
  }

  // repeated string model_list = 8;
  for (int i = 0, n = this->_internal_model_list_size(); i < n; i++) {
    const auto& s = this->_internal_model_list(i);
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      s.data(), static_cast<int>(s.length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "mc.comm.PBDirSpec.model_list");
    target = stream->WriteString(8, s, target);
  }

  // repeated string shader_program_list = 9;
  for (int i = 0, n = this->_internal_shader_program_list_size(); i < n; i++) {
    const auto& s = this->_internal_shader_program_list(i);
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      s.data(), static_cast<int>(s.length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "mc.comm.PBDirSpec.shader_program_list");
    target = stream->WriteString(9, s, target);
  }

  // repeated string material_list = 10;
  for (int i = 0, n = this->_internal_material_list_size(); i < n; i++) {
    const auto& s = this->_internal_material_list(i);
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      s.data(), static_cast<int>(s.length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "mc.comm.PBDirSpec.material_list");
    target = stream->WriteString(10, s, target);
  }

  // repeated string scene_list = 11;
  for (int i = 0, n = this->_internal_scene_list_size(); i < n; i++) {
    const auto& s = this->_internal_scene_list(i);
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      s.data(), static_cast<int>(s.length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "mc.comm.PBDirSpec.scene_list");
    target = stream->WriteString(11, s, target);
  }

  // repeated string node_list = 12;
  for (int i = 0, n = this->_internal_node_list_size(); i < n; i++) {
    const auto& s = this->_internal_node_list(i);
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      s.data(), static_cast<int>(s.length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "mc.comm.PBDirSpec.node_list");
    target = stream->WriteString(12, s, target);
  }

  // repeated string light_list = 13;
  for (int i = 0, n = this->_internal_light_list_size(); i < n; i++) {
    const auto& s = this->_internal_light_list(i);
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      s.data(), static_cast<int>(s.length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "mc.comm.PBDirSpec.light_list");
    target = stream->WriteString(13, s, target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:mc.comm.PBDirSpec)
  return target;
}

size_t PBDirSpec::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:mc.comm.PBDirSpec)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated string image_list = 2;
  total_size += 1 *
      ::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(_impl_.image_list_.size());
  for (int i = 0, n = _impl_.image_list_.size(); i < n; i++) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
      _impl_.image_list_.Get(i));
  }

  // repeated string bin_buffer_list = 3;
  total_size += 1 *
      ::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(_impl_.bin_buffer_list_.size());
  for (int i = 0, n = _impl_.bin_buffer_list_.size(); i < n; i++) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
      _impl_.bin_buffer_list_.Get(i));
  }

  // repeated string shader_code_list = 4;
  total_size += 1 *
      ::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(_impl_.shader_code_list_.size());
  for (int i = 0, n = _impl_.shader_code_list_.size(); i < n; i++) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
      _impl_.shader_code_list_.Get(i));
  }

  // repeated string art_logic_list = 5;
  total_size += 1 *
      ::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(_impl_.art_logic_list_.size());
  for (int i = 0, n = _impl_.art_logic_list_.size(); i < n; i++) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
      _impl_.art_logic_list_.Get(i));
  }

  // repeated string act_logic_list = 6;
  total_size += 1 *
      ::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(_impl_.act_logic_list_.size());
  for (int i = 0, n = _impl_.act_logic_list_.size(); i < n; i++) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
      _impl_.act_logic_list_.Get(i));
  }

  // repeated string texture_list = 7;
  total_size += 1 *
      ::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(_impl_.texture_list_.size());
  for (int i = 0, n = _impl_.texture_list_.size(); i < n; i++) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
      _impl_.texture_list_.Get(i));
  }

  // repeated string model_list = 8;
  total_size += 1 *
      ::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(_impl_.model_list_.size());
  for (int i = 0, n = _impl_.model_list_.size(); i < n; i++) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
      _impl_.model_list_.Get(i));
  }

  // repeated string shader_program_list = 9;
  total_size += 1 *
      ::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(_impl_.shader_program_list_.size());
  for (int i = 0, n = _impl_.shader_program_list_.size(); i < n; i++) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
      _impl_.shader_program_list_.Get(i));
  }

  // repeated string material_list = 10;
  total_size += 1 *
      ::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(_impl_.material_list_.size());
  for (int i = 0, n = _impl_.material_list_.size(); i < n; i++) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
      _impl_.material_list_.Get(i));
  }

  // repeated string scene_list = 11;
  total_size += 1 *
      ::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(_impl_.scene_list_.size());
  for (int i = 0, n = _impl_.scene_list_.size(); i < n; i++) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
      _impl_.scene_list_.Get(i));
  }

  // repeated string node_list = 12;
  total_size += 1 *
      ::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(_impl_.node_list_.size());
  for (int i = 0, n = _impl_.node_list_.size(); i < n; i++) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
      _impl_.node_list_.Get(i));
  }

  // repeated string light_list = 13;
  total_size += 1 *
      ::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(_impl_.light_list_.size());
  for (int i = 0, n = _impl_.light_list_.size(); i < n; i++) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
      _impl_.light_list_.Get(i));
  }

  // string base_dir = 1;
  if (!this->_internal_base_dir().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_base_dir());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData PBDirSpec::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    PBDirSpec::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*PBDirSpec::GetClassData() const { return &_class_data_; }


void PBDirSpec::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<PBDirSpec*>(&to_msg);
  auto& from = static_cast<const PBDirSpec&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:mc.comm.PBDirSpec)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_impl_.image_list_.MergeFrom(from._impl_.image_list_);
  _this->_impl_.bin_buffer_list_.MergeFrom(from._impl_.bin_buffer_list_);
  _this->_impl_.shader_code_list_.MergeFrom(from._impl_.shader_code_list_);
  _this->_impl_.art_logic_list_.MergeFrom(from._impl_.art_logic_list_);
  _this->_impl_.act_logic_list_.MergeFrom(from._impl_.act_logic_list_);
  _this->_impl_.texture_list_.MergeFrom(from._impl_.texture_list_);
  _this->_impl_.model_list_.MergeFrom(from._impl_.model_list_);
  _this->_impl_.shader_program_list_.MergeFrom(from._impl_.shader_program_list_);
  _this->_impl_.material_list_.MergeFrom(from._impl_.material_list_);
  _this->_impl_.scene_list_.MergeFrom(from._impl_.scene_list_);
  _this->_impl_.node_list_.MergeFrom(from._impl_.node_list_);
  _this->_impl_.light_list_.MergeFrom(from._impl_.light_list_);
  if (!from._internal_base_dir().empty()) {
    _this->_internal_set_base_dir(from._internal_base_dir());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void PBDirSpec::CopyFrom(const PBDirSpec& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:mc.comm.PBDirSpec)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PBDirSpec::IsInitialized() const {
  return true;
}

void PBDirSpec::InternalSwap(PBDirSpec* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  _impl_.image_list_.InternalSwap(&other->_impl_.image_list_);
  _impl_.bin_buffer_list_.InternalSwap(&other->_impl_.bin_buffer_list_);
  _impl_.shader_code_list_.InternalSwap(&other->_impl_.shader_code_list_);
  _impl_.art_logic_list_.InternalSwap(&other->_impl_.art_logic_list_);
  _impl_.act_logic_list_.InternalSwap(&other->_impl_.act_logic_list_);
  _impl_.texture_list_.InternalSwap(&other->_impl_.texture_list_);
  _impl_.model_list_.InternalSwap(&other->_impl_.model_list_);
  _impl_.shader_program_list_.InternalSwap(&other->_impl_.shader_program_list_);
  _impl_.material_list_.InternalSwap(&other->_impl_.material_list_);
  _impl_.scene_list_.InternalSwap(&other->_impl_.scene_list_);
  _impl_.node_list_.InternalSwap(&other->_impl_.node_list_);
  _impl_.light_list_.InternalSwap(&other->_impl_.light_list_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.base_dir_, lhs_arena,
      &other->_impl_.base_dir_, rhs_arena
  );
}

::PROTOBUF_NAMESPACE_ID::Metadata PBDirSpec::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_mc_2fcomm_2fpbdirspec_2eproto_getter, &descriptor_table_mc_2fcomm_2fpbdirspec_2eproto_once,
      file_level_metadata_mc_2fcomm_2fpbdirspec_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace comm
}  // namespace mc
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::mc::comm::PBDirSpec*
Arena::CreateMaybeMessage< ::mc::comm::PBDirSpec >(Arena* arena) {
  return Arena::CreateMessageInternal< ::mc::comm::PBDirSpec >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
