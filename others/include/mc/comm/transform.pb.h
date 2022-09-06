// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: mc/comm/transform.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_mc_2fcomm_2ftransform_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_mc_2fcomm_2ftransform_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_mc_2fcomm_2ftransform_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_mc_2fcomm_2ftransform_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_mc_2fcomm_2ftransform_2eproto;
namespace mc {
namespace comm {
class Transform;
struct TransformDefaultTypeInternal;
extern TransformDefaultTypeInternal _Transform_default_instance_;
class Vec3;
struct Vec3DefaultTypeInternal;
extern Vec3DefaultTypeInternal _Vec3_default_instance_;
}  // namespace comm
}  // namespace mc
PROTOBUF_NAMESPACE_OPEN
template<> ::mc::comm::Transform* Arena::CreateMaybeMessage<::mc::comm::Transform>(Arena*);
template<> ::mc::comm::Vec3* Arena::CreateMaybeMessage<::mc::comm::Vec3>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace mc {
namespace comm {

// ===================================================================

class Vec3 final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:mc.comm.Vec3) */ {
 public:
  inline Vec3() : Vec3(nullptr) {}
  ~Vec3() override;
  explicit PROTOBUF_CONSTEXPR Vec3(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Vec3(const Vec3& from);
  Vec3(Vec3&& from) noexcept
    : Vec3() {
    *this = ::std::move(from);
  }

  inline Vec3& operator=(const Vec3& from) {
    CopyFrom(from);
    return *this;
  }
  inline Vec3& operator=(Vec3&& from) noexcept {
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
  static const Vec3& default_instance() {
    return *internal_default_instance();
  }
  static inline const Vec3* internal_default_instance() {
    return reinterpret_cast<const Vec3*>(
               &_Vec3_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Vec3& a, Vec3& b) {
    a.Swap(&b);
  }
  inline void Swap(Vec3* other) {
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
  void UnsafeArenaSwap(Vec3* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Vec3* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Vec3>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Vec3& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const Vec3& from) {
    Vec3::MergeImpl(*this, from);
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
  void InternalSwap(Vec3* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "mc.comm.Vec3";
  }
  protected:
  explicit Vec3(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kXFieldNumber = 1,
    kYFieldNumber = 2,
    kZFieldNumber = 3,
  };
  // float x = 1;
  void clear_x();
  float x() const;
  void set_x(float value);
  private:
  float _internal_x() const;
  void _internal_set_x(float value);
  public:

  // float y = 2;
  void clear_y();
  float y() const;
  void set_y(float value);
  private:
  float _internal_y() const;
  void _internal_set_y(float value);
  public:

  // float z = 3;
  void clear_z();
  float z() const;
  void set_z(float value);
  private:
  float _internal_z() const;
  void _internal_set_z(float value);
  public:

  // @@protoc_insertion_point(class_scope:mc.comm.Vec3)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    float x_;
    float y_;
    float z_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_mc_2fcomm_2ftransform_2eproto;
};
// -------------------------------------------------------------------

class Transform final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:mc.comm.Transform) */ {
 public:
  inline Transform() : Transform(nullptr) {}
  ~Transform() override;
  explicit PROTOBUF_CONSTEXPR Transform(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Transform(const Transform& from);
  Transform(Transform&& from) noexcept
    : Transform() {
    *this = ::std::move(from);
  }

  inline Transform& operator=(const Transform& from) {
    CopyFrom(from);
    return *this;
  }
  inline Transform& operator=(Transform&& from) noexcept {
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
  static const Transform& default_instance() {
    return *internal_default_instance();
  }
  static inline const Transform* internal_default_instance() {
    return reinterpret_cast<const Transform*>(
               &_Transform_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(Transform& a, Transform& b) {
    a.Swap(&b);
  }
  inline void Swap(Transform* other) {
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
  void UnsafeArenaSwap(Transform* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Transform* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Transform>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Transform& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const Transform& from) {
    Transform::MergeImpl(*this, from);
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
  void InternalSwap(Transform* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "mc.comm.Transform";
  }
  protected:
  explicit Transform(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kTranslateFieldNumber = 1,
    kEulerFieldNumber = 2,
    kParentFieldNumber = 3,
  };
  // .mc.comm.Vec3 translate = 1;
  bool has_translate() const;
  private:
  bool _internal_has_translate() const;
  public:
  void clear_translate();
  const ::mc::comm::Vec3& translate() const;
  PROTOBUF_NODISCARD ::mc::comm::Vec3* release_translate();
  ::mc::comm::Vec3* mutable_translate();
  void set_allocated_translate(::mc::comm::Vec3* translate);
  private:
  const ::mc::comm::Vec3& _internal_translate() const;
  ::mc::comm::Vec3* _internal_mutable_translate();
  public:
  void unsafe_arena_set_allocated_translate(
      ::mc::comm::Vec3* translate);
  ::mc::comm::Vec3* unsafe_arena_release_translate();

  // .mc.comm.Vec3 euler = 2;
  bool has_euler() const;
  private:
  bool _internal_has_euler() const;
  public:
  void clear_euler();
  const ::mc::comm::Vec3& euler() const;
  PROTOBUF_NODISCARD ::mc::comm::Vec3* release_euler();
  ::mc::comm::Vec3* mutable_euler();
  void set_allocated_euler(::mc::comm::Vec3* euler);
  private:
  const ::mc::comm::Vec3& _internal_euler() const;
  ::mc::comm::Vec3* _internal_mutable_euler();
  public:
  void unsafe_arena_set_allocated_euler(
      ::mc::comm::Vec3* euler);
  ::mc::comm::Vec3* unsafe_arena_release_euler();

  // .mc.comm.Transform parent = 3;
  bool has_parent() const;
  private:
  bool _internal_has_parent() const;
  public:
  void clear_parent();
  const ::mc::comm::Transform& parent() const;
  PROTOBUF_NODISCARD ::mc::comm::Transform* release_parent();
  ::mc::comm::Transform* mutable_parent();
  void set_allocated_parent(::mc::comm::Transform* parent);
  private:
  const ::mc::comm::Transform& _internal_parent() const;
  ::mc::comm::Transform* _internal_mutable_parent();
  public:
  void unsafe_arena_set_allocated_parent(
      ::mc::comm::Transform* parent);
  ::mc::comm::Transform* unsafe_arena_release_parent();

  // @@protoc_insertion_point(class_scope:mc.comm.Transform)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::mc::comm::Vec3* translate_;
    ::mc::comm::Vec3* euler_;
    ::mc::comm::Transform* parent_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_mc_2fcomm_2ftransform_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Vec3

// float x = 1;
inline void Vec3::clear_x() {
  _impl_.x_ = 0;
}
inline float Vec3::_internal_x() const {
  return _impl_.x_;
}
inline float Vec3::x() const {
  // @@protoc_insertion_point(field_get:mc.comm.Vec3.x)
  return _internal_x();
}
inline void Vec3::_internal_set_x(float value) {
  
  _impl_.x_ = value;
}
inline void Vec3::set_x(float value) {
  _internal_set_x(value);
  // @@protoc_insertion_point(field_set:mc.comm.Vec3.x)
}

// float y = 2;
inline void Vec3::clear_y() {
  _impl_.y_ = 0;
}
inline float Vec3::_internal_y() const {
  return _impl_.y_;
}
inline float Vec3::y() const {
  // @@protoc_insertion_point(field_get:mc.comm.Vec3.y)
  return _internal_y();
}
inline void Vec3::_internal_set_y(float value) {
  
  _impl_.y_ = value;
}
inline void Vec3::set_y(float value) {
  _internal_set_y(value);
  // @@protoc_insertion_point(field_set:mc.comm.Vec3.y)
}

// float z = 3;
inline void Vec3::clear_z() {
  _impl_.z_ = 0;
}
inline float Vec3::_internal_z() const {
  return _impl_.z_;
}
inline float Vec3::z() const {
  // @@protoc_insertion_point(field_get:mc.comm.Vec3.z)
  return _internal_z();
}
inline void Vec3::_internal_set_z(float value) {
  
  _impl_.z_ = value;
}
inline void Vec3::set_z(float value) {
  _internal_set_z(value);
  // @@protoc_insertion_point(field_set:mc.comm.Vec3.z)
}

// -------------------------------------------------------------------

// Transform

// .mc.comm.Vec3 translate = 1;
inline bool Transform::_internal_has_translate() const {
  return this != internal_default_instance() && _impl_.translate_ != nullptr;
}
inline bool Transform::has_translate() const {
  return _internal_has_translate();
}
inline void Transform::clear_translate() {
  if (GetArenaForAllocation() == nullptr && _impl_.translate_ != nullptr) {
    delete _impl_.translate_;
  }
  _impl_.translate_ = nullptr;
}
inline const ::mc::comm::Vec3& Transform::_internal_translate() const {
  const ::mc::comm::Vec3* p = _impl_.translate_;
  return p != nullptr ? *p : reinterpret_cast<const ::mc::comm::Vec3&>(
      ::mc::comm::_Vec3_default_instance_);
}
inline const ::mc::comm::Vec3& Transform::translate() const {
  // @@protoc_insertion_point(field_get:mc.comm.Transform.translate)
  return _internal_translate();
}
inline void Transform::unsafe_arena_set_allocated_translate(
    ::mc::comm::Vec3* translate) {
  if (GetArenaForAllocation() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(_impl_.translate_);
  }
  _impl_.translate_ = translate;
  if (translate) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:mc.comm.Transform.translate)
}
inline ::mc::comm::Vec3* Transform::release_translate() {
  
  ::mc::comm::Vec3* temp = _impl_.translate_;
  _impl_.translate_ = nullptr;
#ifdef PROTOBUF_FORCE_COPY_IN_RELEASE
  auto* old =  reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(temp);
  temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  if (GetArenaForAllocation() == nullptr) { delete old; }
#else  // PROTOBUF_FORCE_COPY_IN_RELEASE
  if (GetArenaForAllocation() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
#endif  // !PROTOBUF_FORCE_COPY_IN_RELEASE
  return temp;
}
inline ::mc::comm::Vec3* Transform::unsafe_arena_release_translate() {
  // @@protoc_insertion_point(field_release:mc.comm.Transform.translate)
  
  ::mc::comm::Vec3* temp = _impl_.translate_;
  _impl_.translate_ = nullptr;
  return temp;
}
inline ::mc::comm::Vec3* Transform::_internal_mutable_translate() {
  
  if (_impl_.translate_ == nullptr) {
    auto* p = CreateMaybeMessage<::mc::comm::Vec3>(GetArenaForAllocation());
    _impl_.translate_ = p;
  }
  return _impl_.translate_;
}
inline ::mc::comm::Vec3* Transform::mutable_translate() {
  ::mc::comm::Vec3* _msg = _internal_mutable_translate();
  // @@protoc_insertion_point(field_mutable:mc.comm.Transform.translate)
  return _msg;
}
inline void Transform::set_allocated_translate(::mc::comm::Vec3* translate) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  if (message_arena == nullptr) {
    delete _impl_.translate_;
  }
  if (translate) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalGetOwningArena(translate);
    if (message_arena != submessage_arena) {
      translate = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, translate, submessage_arena);
    }
    
  } else {
    
  }
  _impl_.translate_ = translate;
  // @@protoc_insertion_point(field_set_allocated:mc.comm.Transform.translate)
}

// .mc.comm.Vec3 euler = 2;
inline bool Transform::_internal_has_euler() const {
  return this != internal_default_instance() && _impl_.euler_ != nullptr;
}
inline bool Transform::has_euler() const {
  return _internal_has_euler();
}
inline void Transform::clear_euler() {
  if (GetArenaForAllocation() == nullptr && _impl_.euler_ != nullptr) {
    delete _impl_.euler_;
  }
  _impl_.euler_ = nullptr;
}
inline const ::mc::comm::Vec3& Transform::_internal_euler() const {
  const ::mc::comm::Vec3* p = _impl_.euler_;
  return p != nullptr ? *p : reinterpret_cast<const ::mc::comm::Vec3&>(
      ::mc::comm::_Vec3_default_instance_);
}
inline const ::mc::comm::Vec3& Transform::euler() const {
  // @@protoc_insertion_point(field_get:mc.comm.Transform.euler)
  return _internal_euler();
}
inline void Transform::unsafe_arena_set_allocated_euler(
    ::mc::comm::Vec3* euler) {
  if (GetArenaForAllocation() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(_impl_.euler_);
  }
  _impl_.euler_ = euler;
  if (euler) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:mc.comm.Transform.euler)
}
inline ::mc::comm::Vec3* Transform::release_euler() {
  
  ::mc::comm::Vec3* temp = _impl_.euler_;
  _impl_.euler_ = nullptr;
#ifdef PROTOBUF_FORCE_COPY_IN_RELEASE
  auto* old =  reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(temp);
  temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  if (GetArenaForAllocation() == nullptr) { delete old; }
#else  // PROTOBUF_FORCE_COPY_IN_RELEASE
  if (GetArenaForAllocation() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
#endif  // !PROTOBUF_FORCE_COPY_IN_RELEASE
  return temp;
}
inline ::mc::comm::Vec3* Transform::unsafe_arena_release_euler() {
  // @@protoc_insertion_point(field_release:mc.comm.Transform.euler)
  
  ::mc::comm::Vec3* temp = _impl_.euler_;
  _impl_.euler_ = nullptr;
  return temp;
}
inline ::mc::comm::Vec3* Transform::_internal_mutable_euler() {
  
  if (_impl_.euler_ == nullptr) {
    auto* p = CreateMaybeMessage<::mc::comm::Vec3>(GetArenaForAllocation());
    _impl_.euler_ = p;
  }
  return _impl_.euler_;
}
inline ::mc::comm::Vec3* Transform::mutable_euler() {
  ::mc::comm::Vec3* _msg = _internal_mutable_euler();
  // @@protoc_insertion_point(field_mutable:mc.comm.Transform.euler)
  return _msg;
}
inline void Transform::set_allocated_euler(::mc::comm::Vec3* euler) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  if (message_arena == nullptr) {
    delete _impl_.euler_;
  }
  if (euler) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalGetOwningArena(euler);
    if (message_arena != submessage_arena) {
      euler = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, euler, submessage_arena);
    }
    
  } else {
    
  }
  _impl_.euler_ = euler;
  // @@protoc_insertion_point(field_set_allocated:mc.comm.Transform.euler)
}

// .mc.comm.Transform parent = 3;
inline bool Transform::_internal_has_parent() const {
  return this != internal_default_instance() && _impl_.parent_ != nullptr;
}
inline bool Transform::has_parent() const {
  return _internal_has_parent();
}
inline void Transform::clear_parent() {
  if (GetArenaForAllocation() == nullptr && _impl_.parent_ != nullptr) {
    delete _impl_.parent_;
  }
  _impl_.parent_ = nullptr;
}
inline const ::mc::comm::Transform& Transform::_internal_parent() const {
  const ::mc::comm::Transform* p = _impl_.parent_;
  return p != nullptr ? *p : reinterpret_cast<const ::mc::comm::Transform&>(
      ::mc::comm::_Transform_default_instance_);
}
inline const ::mc::comm::Transform& Transform::parent() const {
  // @@protoc_insertion_point(field_get:mc.comm.Transform.parent)
  return _internal_parent();
}
inline void Transform::unsafe_arena_set_allocated_parent(
    ::mc::comm::Transform* parent) {
  if (GetArenaForAllocation() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(_impl_.parent_);
  }
  _impl_.parent_ = parent;
  if (parent) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:mc.comm.Transform.parent)
}
inline ::mc::comm::Transform* Transform::release_parent() {
  
  ::mc::comm::Transform* temp = _impl_.parent_;
  _impl_.parent_ = nullptr;
#ifdef PROTOBUF_FORCE_COPY_IN_RELEASE
  auto* old =  reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(temp);
  temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  if (GetArenaForAllocation() == nullptr) { delete old; }
#else  // PROTOBUF_FORCE_COPY_IN_RELEASE
  if (GetArenaForAllocation() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
#endif  // !PROTOBUF_FORCE_COPY_IN_RELEASE
  return temp;
}
inline ::mc::comm::Transform* Transform::unsafe_arena_release_parent() {
  // @@protoc_insertion_point(field_release:mc.comm.Transform.parent)
  
  ::mc::comm::Transform* temp = _impl_.parent_;
  _impl_.parent_ = nullptr;
  return temp;
}
inline ::mc::comm::Transform* Transform::_internal_mutable_parent() {
  
  if (_impl_.parent_ == nullptr) {
    auto* p = CreateMaybeMessage<::mc::comm::Transform>(GetArenaForAllocation());
    _impl_.parent_ = p;
  }
  return _impl_.parent_;
}
inline ::mc::comm::Transform* Transform::mutable_parent() {
  ::mc::comm::Transform* _msg = _internal_mutable_parent();
  // @@protoc_insertion_point(field_mutable:mc.comm.Transform.parent)
  return _msg;
}
inline void Transform::set_allocated_parent(::mc::comm::Transform* parent) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  if (message_arena == nullptr) {
    delete _impl_.parent_;
  }
  if (parent) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalGetOwningArena(parent);
    if (message_arena != submessage_arena) {
      parent = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, parent, submessage_arena);
    }
    
  } else {
    
  }
  _impl_.parent_ = parent;
  // @@protoc_insertion_point(field_set_allocated:mc.comm.Transform.parent)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace comm
}  // namespace mc

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_mc_2fcomm_2ftransform_2eproto
