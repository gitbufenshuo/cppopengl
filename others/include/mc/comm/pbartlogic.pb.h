// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: mc/comm/pbartlogic.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_mc_2fcomm_2fpbartlogic_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_mc_2fcomm_2fpbartlogic_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021005 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_mc_2fcomm_2fpbartlogic_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_mc_2fcomm_2fpbartlogic_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_mc_2fcomm_2fpbartlogic_2eproto;
namespace mc {
namespace comm {
class PBArtLogic;
struct PBArtLogicDefaultTypeInternal;
extern PBArtLogicDefaultTypeInternal _PBArtLogic_default_instance_;
}  // namespace comm
}  // namespace mc
PROTOBUF_NAMESPACE_OPEN
template<> ::mc::comm::PBArtLogic* Arena::CreateMaybeMessage<::mc::comm::PBArtLogic>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace mc {
namespace comm {

// ===================================================================

class PBArtLogic final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:mc.comm.PBArtLogic) */ {
 public:
  inline PBArtLogic() : PBArtLogic(nullptr) {}
  ~PBArtLogic() override;
  explicit PROTOBUF_CONSTEXPR PBArtLogic(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  PBArtLogic(const PBArtLogic& from);
  PBArtLogic(PBArtLogic&& from) noexcept
    : PBArtLogic() {
    *this = ::std::move(from);
  }

  inline PBArtLogic& operator=(const PBArtLogic& from) {
    CopyFrom(from);
    return *this;
  }
  inline PBArtLogic& operator=(PBArtLogic&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const PBArtLogic& default_instance() {
    return *internal_default_instance();
  }
  static inline const PBArtLogic* internal_default_instance() {
    return reinterpret_cast<const PBArtLogic*>(
               &_PBArtLogic_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(PBArtLogic& a, PBArtLogic& b) {
    a.Swap(&b);
  }
  inline void Swap(PBArtLogic* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(PBArtLogic* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  PBArtLogic* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<PBArtLogic>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const PBArtLogic& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const PBArtLogic& from) {
    PBArtLogic::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(PBArtLogic* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "mc.comm.PBArtLogic";
  }
  protected:
  explicit PBArtLogic(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kLogicClassFieldNumber = 1,
    kPropertiesFieldNumber = 2,
  };
  // string logic_class = 1;
  void clear_logic_class();
  const std::string& logic_class() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_logic_class(ArgT0&& arg0, ArgT... args);
  std::string* mutable_logic_class();
  PROTOBUF_NODISCARD std::string* release_logic_class();
  void set_allocated_logic_class(std::string* logic_class);
  private:
  const std::string& _internal_logic_class() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_logic_class(const std::string& value);
  std::string* _internal_mutable_logic_class();
  public:

  // string properties = 2;
  void clear_properties();
  const std::string& properties() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_properties(ArgT0&& arg0, ArgT... args);
  std::string* mutable_properties();
  PROTOBUF_NODISCARD std::string* release_properties();
  void set_allocated_properties(std::string* properties);
  private:
  const std::string& _internal_properties() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_properties(const std::string& value);
  std::string* _internal_mutable_properties();
  public:

  // @@protoc_insertion_point(class_scope:mc.comm.PBArtLogic)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr logic_class_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr properties_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_mc_2fcomm_2fpbartlogic_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// PBArtLogic

// string logic_class = 1;
inline void PBArtLogic::clear_logic_class() {
  _impl_.logic_class_.ClearToEmpty();
}
inline const std::string& PBArtLogic::logic_class() const {
  // @@protoc_insertion_point(field_get:mc.comm.PBArtLogic.logic_class)
  return _internal_logic_class();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void PBArtLogic::set_logic_class(ArgT0&& arg0, ArgT... args) {
 
 _impl_.logic_class_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:mc.comm.PBArtLogic.logic_class)
}
inline std::string* PBArtLogic::mutable_logic_class() {
  std::string* _s = _internal_mutable_logic_class();
  // @@protoc_insertion_point(field_mutable:mc.comm.PBArtLogic.logic_class)
  return _s;
}
inline const std::string& PBArtLogic::_internal_logic_class() const {
  return _impl_.logic_class_.Get();
}
inline void PBArtLogic::_internal_set_logic_class(const std::string& value) {
  
  _impl_.logic_class_.Set(value, GetArenaForAllocation());
}
inline std::string* PBArtLogic::_internal_mutable_logic_class() {
  
  return _impl_.logic_class_.Mutable(GetArenaForAllocation());
}
inline std::string* PBArtLogic::release_logic_class() {
  // @@protoc_insertion_point(field_release:mc.comm.PBArtLogic.logic_class)
  return _impl_.logic_class_.Release();
}
inline void PBArtLogic::set_allocated_logic_class(std::string* logic_class) {
  if (logic_class != nullptr) {
    
  } else {
    
  }
  _impl_.logic_class_.SetAllocated(logic_class, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.logic_class_.IsDefault()) {
    _impl_.logic_class_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:mc.comm.PBArtLogic.logic_class)
}

// string properties = 2;
inline void PBArtLogic::clear_properties() {
  _impl_.properties_.ClearToEmpty();
}
inline const std::string& PBArtLogic::properties() const {
  // @@protoc_insertion_point(field_get:mc.comm.PBArtLogic.properties)
  return _internal_properties();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void PBArtLogic::set_properties(ArgT0&& arg0, ArgT... args) {
 
 _impl_.properties_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:mc.comm.PBArtLogic.properties)
}
inline std::string* PBArtLogic::mutable_properties() {
  std::string* _s = _internal_mutable_properties();
  // @@protoc_insertion_point(field_mutable:mc.comm.PBArtLogic.properties)
  return _s;
}
inline const std::string& PBArtLogic::_internal_properties() const {
  return _impl_.properties_.Get();
}
inline void PBArtLogic::_internal_set_properties(const std::string& value) {
  
  _impl_.properties_.Set(value, GetArenaForAllocation());
}
inline std::string* PBArtLogic::_internal_mutable_properties() {
  
  return _impl_.properties_.Mutable(GetArenaForAllocation());
}
inline std::string* PBArtLogic::release_properties() {
  // @@protoc_insertion_point(field_release:mc.comm.PBArtLogic.properties)
  return _impl_.properties_.Release();
}
inline void PBArtLogic::set_allocated_properties(std::string* properties) {
  if (properties != nullptr) {
    
  } else {
    
  }
  _impl_.properties_.SetAllocated(properties, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.properties_.IsDefault()) {
    _impl_.properties_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:mc.comm.PBArtLogic.properties)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace comm
}  // namespace mc

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_mc_2fcomm_2fpbartlogic_2eproto