// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: mc/comm/pbmodel.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_mc_2fcomm_2fpbmodel_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_mc_2fcomm_2fpbmodel_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_mc_2fcomm_2fpbmodel_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_mc_2fcomm_2fpbmodel_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_mc_2fcomm_2fpbmodel_2eproto;
namespace mc {
namespace comm {
class PBModel;
struct PBModelDefaultTypeInternal;
extern PBModelDefaultTypeInternal _PBModel_default_instance_;
}  // namespace comm
}  // namespace mc
PROTOBUF_NAMESPACE_OPEN
template<> ::mc::comm::PBModel* Arena::CreateMaybeMessage<::mc::comm::PBModel>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace mc {
namespace comm {

// ===================================================================

class PBModel final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:mc.comm.PBModel) */ {
 public:
  inline PBModel() : PBModel(nullptr) {}
  ~PBModel() override;
  explicit PROTOBUF_CONSTEXPR PBModel(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  PBModel(const PBModel& from);
  PBModel(PBModel&& from) noexcept
    : PBModel() {
    *this = ::std::move(from);
  }

  inline PBModel& operator=(const PBModel& from) {
    CopyFrom(from);
    return *this;
  }
  inline PBModel& operator=(PBModel&& from) noexcept {
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
  static const PBModel& default_instance() {
    return *internal_default_instance();
  }
  static inline const PBModel* internal_default_instance() {
    return reinterpret_cast<const PBModel*>(
               &_PBModel_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(PBModel& a, PBModel& b) {
    a.Swap(&b);
  }
  inline void Swap(PBModel* other) {
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
  void UnsafeArenaSwap(PBModel* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  PBModel* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<PBModel>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const PBModel& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const PBModel& from) {
    PBModel::MergeImpl(*this, from);
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
  void InternalSwap(PBModel* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "mc.comm.PBModel";
  }
  protected:
  explicit PBModel(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kAttribFieldNumber = 6,
    kBinBufferFieldNumber = 1,
    kBeginFieldNumber = 2,
    kLengthFieldNumber = 3,
    kEboLengthFieldNumber = 4,
    kEboTypeFieldNumber = 5,
  };
  // repeated int32 attrib = 6;
  int attrib_size() const;
  private:
  int _internal_attrib_size() const;
  public:
  void clear_attrib();
  private:
  int32_t _internal_attrib(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >&
      _internal_attrib() const;
  void _internal_add_attrib(int32_t value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >*
      _internal_mutable_attrib();
  public:
  int32_t attrib(int index) const;
  void set_attrib(int index, int32_t value);
  void add_attrib(int32_t value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >&
      attrib() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >*
      mutable_attrib();

  // string bin_buffer = 1;
  void clear_bin_buffer();
  const std::string& bin_buffer() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_bin_buffer(ArgT0&& arg0, ArgT... args);
  std::string* mutable_bin_buffer();
  PROTOBUF_NODISCARD std::string* release_bin_buffer();
  void set_allocated_bin_buffer(std::string* bin_buffer);
  private:
  const std::string& _internal_bin_buffer() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_bin_buffer(const std::string& value);
  std::string* _internal_mutable_bin_buffer();
  public:

  // int32 begin = 2;
  void clear_begin();
  int32_t begin() const;
  void set_begin(int32_t value);
  private:
  int32_t _internal_begin() const;
  void _internal_set_begin(int32_t value);
  public:

  // int32 length = 3;
  void clear_length();
  int32_t length() const;
  void set_length(int32_t value);
  private:
  int32_t _internal_length() const;
  void _internal_set_length(int32_t value);
  public:

  // int32 ebo_length = 4;
  void clear_ebo_length();
  int32_t ebo_length() const;
  void set_ebo_length(int32_t value);
  private:
  int32_t _internal_ebo_length() const;
  void _internal_set_ebo_length(int32_t value);
  public:

  // int32 ebo_type = 5;
  void clear_ebo_type();
  int32_t ebo_type() const;
  void set_ebo_type(int32_t value);
  private:
  int32_t _internal_ebo_type() const;
  void _internal_set_ebo_type(int32_t value);
  public:

  // @@protoc_insertion_point(class_scope:mc.comm.PBModel)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t > attrib_;
    mutable std::atomic<int> _attrib_cached_byte_size_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr bin_buffer_;
    int32_t begin_;
    int32_t length_;
    int32_t ebo_length_;
    int32_t ebo_type_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_mc_2fcomm_2fpbmodel_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// PBModel

// string bin_buffer = 1;
inline void PBModel::clear_bin_buffer() {
  _impl_.bin_buffer_.ClearToEmpty();
}
inline const std::string& PBModel::bin_buffer() const {
  // @@protoc_insertion_point(field_get:mc.comm.PBModel.bin_buffer)
  return _internal_bin_buffer();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void PBModel::set_bin_buffer(ArgT0&& arg0, ArgT... args) {
 
 _impl_.bin_buffer_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:mc.comm.PBModel.bin_buffer)
}
inline std::string* PBModel::mutable_bin_buffer() {
  std::string* _s = _internal_mutable_bin_buffer();
  // @@protoc_insertion_point(field_mutable:mc.comm.PBModel.bin_buffer)
  return _s;
}
inline const std::string& PBModel::_internal_bin_buffer() const {
  return _impl_.bin_buffer_.Get();
}
inline void PBModel::_internal_set_bin_buffer(const std::string& value) {
  
  _impl_.bin_buffer_.Set(value, GetArenaForAllocation());
}
inline std::string* PBModel::_internal_mutable_bin_buffer() {
  
  return _impl_.bin_buffer_.Mutable(GetArenaForAllocation());
}
inline std::string* PBModel::release_bin_buffer() {
  // @@protoc_insertion_point(field_release:mc.comm.PBModel.bin_buffer)
  return _impl_.bin_buffer_.Release();
}
inline void PBModel::set_allocated_bin_buffer(std::string* bin_buffer) {
  if (bin_buffer != nullptr) {
    
  } else {
    
  }
  _impl_.bin_buffer_.SetAllocated(bin_buffer, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.bin_buffer_.IsDefault()) {
    _impl_.bin_buffer_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:mc.comm.PBModel.bin_buffer)
}

// int32 begin = 2;
inline void PBModel::clear_begin() {
  _impl_.begin_ = 0;
}
inline int32_t PBModel::_internal_begin() const {
  return _impl_.begin_;
}
inline int32_t PBModel::begin() const {
  // @@protoc_insertion_point(field_get:mc.comm.PBModel.begin)
  return _internal_begin();
}
inline void PBModel::_internal_set_begin(int32_t value) {
  
  _impl_.begin_ = value;
}
inline void PBModel::set_begin(int32_t value) {
  _internal_set_begin(value);
  // @@protoc_insertion_point(field_set:mc.comm.PBModel.begin)
}

// int32 length = 3;
inline void PBModel::clear_length() {
  _impl_.length_ = 0;
}
inline int32_t PBModel::_internal_length() const {
  return _impl_.length_;
}
inline int32_t PBModel::length() const {
  // @@protoc_insertion_point(field_get:mc.comm.PBModel.length)
  return _internal_length();
}
inline void PBModel::_internal_set_length(int32_t value) {
  
  _impl_.length_ = value;
}
inline void PBModel::set_length(int32_t value) {
  _internal_set_length(value);
  // @@protoc_insertion_point(field_set:mc.comm.PBModel.length)
}

// int32 ebo_length = 4;
inline void PBModel::clear_ebo_length() {
  _impl_.ebo_length_ = 0;
}
inline int32_t PBModel::_internal_ebo_length() const {
  return _impl_.ebo_length_;
}
inline int32_t PBModel::ebo_length() const {
  // @@protoc_insertion_point(field_get:mc.comm.PBModel.ebo_length)
  return _internal_ebo_length();
}
inline void PBModel::_internal_set_ebo_length(int32_t value) {
  
  _impl_.ebo_length_ = value;
}
inline void PBModel::set_ebo_length(int32_t value) {
  _internal_set_ebo_length(value);
  // @@protoc_insertion_point(field_set:mc.comm.PBModel.ebo_length)
}

// int32 ebo_type = 5;
inline void PBModel::clear_ebo_type() {
  _impl_.ebo_type_ = 0;
}
inline int32_t PBModel::_internal_ebo_type() const {
  return _impl_.ebo_type_;
}
inline int32_t PBModel::ebo_type() const {
  // @@protoc_insertion_point(field_get:mc.comm.PBModel.ebo_type)
  return _internal_ebo_type();
}
inline void PBModel::_internal_set_ebo_type(int32_t value) {
  
  _impl_.ebo_type_ = value;
}
inline void PBModel::set_ebo_type(int32_t value) {
  _internal_set_ebo_type(value);
  // @@protoc_insertion_point(field_set:mc.comm.PBModel.ebo_type)
}

// repeated int32 attrib = 6;
inline int PBModel::_internal_attrib_size() const {
  return _impl_.attrib_.size();
}
inline int PBModel::attrib_size() const {
  return _internal_attrib_size();
}
inline void PBModel::clear_attrib() {
  _impl_.attrib_.Clear();
}
inline int32_t PBModel::_internal_attrib(int index) const {
  return _impl_.attrib_.Get(index);
}
inline int32_t PBModel::attrib(int index) const {
  // @@protoc_insertion_point(field_get:mc.comm.PBModel.attrib)
  return _internal_attrib(index);
}
inline void PBModel::set_attrib(int index, int32_t value) {
  _impl_.attrib_.Set(index, value);
  // @@protoc_insertion_point(field_set:mc.comm.PBModel.attrib)
}
inline void PBModel::_internal_add_attrib(int32_t value) {
  _impl_.attrib_.Add(value);
}
inline void PBModel::add_attrib(int32_t value) {
  _internal_add_attrib(value);
  // @@protoc_insertion_point(field_add:mc.comm.PBModel.attrib)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >&
PBModel::_internal_attrib() const {
  return _impl_.attrib_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >&
PBModel::attrib() const {
  // @@protoc_insertion_point(field_list:mc.comm.PBModel.attrib)
  return _internal_attrib();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >*
PBModel::_internal_mutable_attrib() {
  return &_impl_.attrib_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >*
PBModel::mutable_attrib() {
  // @@protoc_insertion_point(field_mutable_list:mc.comm.PBModel.attrib)
  return _internal_mutable_attrib();
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace comm
}  // namespace mc

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_mc_2fcomm_2fpbmodel_2eproto
