// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: frontend.proto

#include "frontend.pb.h"

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

PROTOBUF_CONSTEXPR F2BChangeAddress::F2BChangeAddress(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_._has_bits_)*/{}
  , /*decltype(_impl_._cached_size_)*/{}
  , /*decltype(_impl_.seqnum_)*/int64_t{0}
  , /*decltype(_impl_.shipid_)*/int64_t{0}
  , /*decltype(_impl_.x_)*/0
  , /*decltype(_impl_.y_)*/0} {}
struct F2BChangeAddressDefaultTypeInternal {
  PROTOBUF_CONSTEXPR F2BChangeAddressDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~F2BChangeAddressDefaultTypeInternal() {}
  union {
    F2BChangeAddress _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 F2BChangeAddressDefaultTypeInternal _F2BChangeAddress_default_instance_;
PROTOBUF_CONSTEXPR B2FChangeAddressResp::B2FChangeAddressResp(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_._has_bits_)*/{}
  , /*decltype(_impl_._cached_size_)*/{}
  , /*decltype(_impl_.seqnum_)*/int64_t{0}
  , /*decltype(_impl_.shipid_)*/int64_t{0}
  , /*decltype(_impl_.result_)*/0} {}
struct B2FChangeAddressRespDefaultTypeInternal {
  PROTOBUF_CONSTEXPR B2FChangeAddressRespDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~B2FChangeAddressRespDefaultTypeInternal() {}
  union {
    B2FChangeAddressResp _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 B2FChangeAddressRespDefaultTypeInternal _B2FChangeAddressResp_default_instance_;
static ::_pb::Metadata file_level_metadata_frontend_2eproto[2];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_frontend_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_frontend_2eproto = nullptr;

const uint32_t TableStruct_frontend_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::F2BChangeAddress, _impl_._has_bits_),
  PROTOBUF_FIELD_OFFSET(::F2BChangeAddress, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::F2BChangeAddress, _impl_.seqnum_),
  PROTOBUF_FIELD_OFFSET(::F2BChangeAddress, _impl_.shipid_),
  PROTOBUF_FIELD_OFFSET(::F2BChangeAddress, _impl_.x_),
  PROTOBUF_FIELD_OFFSET(::F2BChangeAddress, _impl_.y_),
  0,
  1,
  2,
  3,
  PROTOBUF_FIELD_OFFSET(::B2FChangeAddressResp, _impl_._has_bits_),
  PROTOBUF_FIELD_OFFSET(::B2FChangeAddressResp, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::B2FChangeAddressResp, _impl_.seqnum_),
  PROTOBUF_FIELD_OFFSET(::B2FChangeAddressResp, _impl_.shipid_),
  PROTOBUF_FIELD_OFFSET(::B2FChangeAddressResp, _impl_.result_),
  0,
  1,
  2,
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 10, -1, sizeof(::F2BChangeAddress)},
  { 14, 23, -1, sizeof(::B2FChangeAddressResp)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::_F2BChangeAddress_default_instance_._instance,
  &::_B2FChangeAddressResp_default_instance_._instance,
};

const char descriptor_table_protodef_frontend_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\016frontend.proto\"H\n\020F2BChangeAddress\022\016\n\006"
  "seqnum\030\001 \002(\003\022\016\n\006shipid\030\002 \002(\003\022\t\n\001x\030\003 \002(\005\022"
  "\t\n\001y\030\004 \002(\005\"F\n\024B2FChangeAddressResp\022\016\n\006se"
  "qnum\030\001 \002(\003\022\016\n\006shipid\030\002 \002(\003\022\016\n\006result\030\003 \002"
  "(\005"
  ;
static ::_pbi::once_flag descriptor_table_frontend_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_frontend_2eproto = {
    false, false, 162, descriptor_table_protodef_frontend_2eproto,
    "frontend.proto",
    &descriptor_table_frontend_2eproto_once, nullptr, 0, 2,
    schemas, file_default_instances, TableStruct_frontend_2eproto::offsets,
    file_level_metadata_frontend_2eproto, file_level_enum_descriptors_frontend_2eproto,
    file_level_service_descriptors_frontend_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_frontend_2eproto_getter() {
  return &descriptor_table_frontend_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_frontend_2eproto(&descriptor_table_frontend_2eproto);

// ===================================================================

class F2BChangeAddress::_Internal {
 public:
  using HasBits = decltype(std::declval<F2BChangeAddress>()._impl_._has_bits_);
  static void set_has_seqnum(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_shipid(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static void set_has_x(HasBits* has_bits) {
    (*has_bits)[0] |= 4u;
  }
  static void set_has_y(HasBits* has_bits) {
    (*has_bits)[0] |= 8u;
  }
  static bool MissingRequiredFields(const HasBits& has_bits) {
    return ((has_bits[0] & 0x0000000f) ^ 0x0000000f) != 0;
  }
};

F2BChangeAddress::F2BChangeAddress(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:F2BChangeAddress)
}
F2BChangeAddress::F2BChangeAddress(const F2BChangeAddress& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){from._impl_._has_bits_}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.seqnum_){}
    , decltype(_impl_.shipid_){}
    , decltype(_impl_.x_){}
    , decltype(_impl_.y_){}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&_impl_.seqnum_, &from._impl_.seqnum_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.y_) -
    reinterpret_cast<char*>(&_impl_.seqnum_)) + sizeof(_impl_.y_));
  // @@protoc_insertion_point(copy_constructor:F2BChangeAddress)
}

inline void F2BChangeAddress::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.seqnum_){int64_t{0}}
    , decltype(_impl_.shipid_){int64_t{0}}
    , decltype(_impl_.x_){0}
    , decltype(_impl_.y_){0}
  };
}

F2BChangeAddress::~F2BChangeAddress() {
  // @@protoc_insertion_point(destructor:F2BChangeAddress)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void F2BChangeAddress::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void F2BChangeAddress::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void F2BChangeAddress::Clear() {
// @@protoc_insertion_point(message_clear_start:F2BChangeAddress)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x0000000fu) {
    ::memset(&_impl_.seqnum_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&_impl_.y_) -
        reinterpret_cast<char*>(&_impl_.seqnum_)) + sizeof(_impl_.y_));
  }
  _impl_._has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* F2BChangeAddress::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // required int64 seqnum = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _Internal::set_has_seqnum(&has_bits);
          _impl_.seqnum_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // required int64 shipid = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          _Internal::set_has_shipid(&has_bits);
          _impl_.shipid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // required int32 x = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 24)) {
          _Internal::set_has_x(&has_bits);
          _impl_.x_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // required int32 y = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 32)) {
          _Internal::set_has_y(&has_bits);
          _impl_.y_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
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
  _impl_._has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* F2BChangeAddress::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:F2BChangeAddress)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  // required int64 seqnum = 1;
  if (cached_has_bits & 0x00000001u) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt64ToArray(1, this->_internal_seqnum(), target);
  }

  // required int64 shipid = 2;
  if (cached_has_bits & 0x00000002u) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt64ToArray(2, this->_internal_shipid(), target);
  }

  // required int32 x = 3;
  if (cached_has_bits & 0x00000004u) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(3, this->_internal_x(), target);
  }

  // required int32 y = 4;
  if (cached_has_bits & 0x00000008u) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(4, this->_internal_y(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:F2BChangeAddress)
  return target;
}

size_t F2BChangeAddress::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:F2BChangeAddress)
  size_t total_size = 0;

  if (_internal_has_seqnum()) {
    // required int64 seqnum = 1;
    total_size += ::_pbi::WireFormatLite::Int64SizePlusOne(this->_internal_seqnum());
  }

  if (_internal_has_shipid()) {
    // required int64 shipid = 2;
    total_size += ::_pbi::WireFormatLite::Int64SizePlusOne(this->_internal_shipid());
  }

  if (_internal_has_x()) {
    // required int32 x = 3;
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_x());
  }

  if (_internal_has_y()) {
    // required int32 y = 4;
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_y());
  }

  return total_size;
}
size_t F2BChangeAddress::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:F2BChangeAddress)
  size_t total_size = 0;

  if (((_impl_._has_bits_[0] & 0x0000000f) ^ 0x0000000f) == 0) {  // All required fields are present.
    // required int64 seqnum = 1;
    total_size += ::_pbi::WireFormatLite::Int64SizePlusOne(this->_internal_seqnum());

    // required int64 shipid = 2;
    total_size += ::_pbi::WireFormatLite::Int64SizePlusOne(this->_internal_shipid());

    // required int32 x = 3;
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_x());

    // required int32 y = 4;
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_y());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData F2BChangeAddress::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    F2BChangeAddress::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*F2BChangeAddress::GetClassData() const { return &_class_data_; }

void F2BChangeAddress::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<F2BChangeAddress *>(to)->MergeFrom(
      static_cast<const F2BChangeAddress &>(from));
}


void F2BChangeAddress::MergeFrom(const F2BChangeAddress& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:F2BChangeAddress)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._impl_._has_bits_[0];
  if (cached_has_bits & 0x0000000fu) {
    if (cached_has_bits & 0x00000001u) {
      _impl_.seqnum_ = from._impl_.seqnum_;
    }
    if (cached_has_bits & 0x00000002u) {
      _impl_.shipid_ = from._impl_.shipid_;
    }
    if (cached_has_bits & 0x00000004u) {
      _impl_.x_ = from._impl_.x_;
    }
    if (cached_has_bits & 0x00000008u) {
      _impl_.y_ = from._impl_.y_;
    }
    _impl_._has_bits_[0] |= cached_has_bits;
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void F2BChangeAddress::CopyFrom(const F2BChangeAddress& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:F2BChangeAddress)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool F2BChangeAddress::IsInitialized() const {
  if (_Internal::MissingRequiredFields(_impl_._has_bits_)) return false;
  return true;
}

void F2BChangeAddress::InternalSwap(F2BChangeAddress* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_._has_bits_[0], other->_impl_._has_bits_[0]);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(F2BChangeAddress, _impl_.y_)
      + sizeof(F2BChangeAddress::_impl_.y_)
      - PROTOBUF_FIELD_OFFSET(F2BChangeAddress, _impl_.seqnum_)>(
          reinterpret_cast<char*>(&_impl_.seqnum_),
          reinterpret_cast<char*>(&other->_impl_.seqnum_));
}

::PROTOBUF_NAMESPACE_ID::Metadata F2BChangeAddress::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_frontend_2eproto_getter, &descriptor_table_frontend_2eproto_once,
      file_level_metadata_frontend_2eproto[0]);
}

// ===================================================================

class B2FChangeAddressResp::_Internal {
 public:
  using HasBits = decltype(std::declval<B2FChangeAddressResp>()._impl_._has_bits_);
  static void set_has_seqnum(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_shipid(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static void set_has_result(HasBits* has_bits) {
    (*has_bits)[0] |= 4u;
  }
  static bool MissingRequiredFields(const HasBits& has_bits) {
    return ((has_bits[0] & 0x00000007) ^ 0x00000007) != 0;
  }
};

B2FChangeAddressResp::B2FChangeAddressResp(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:B2FChangeAddressResp)
}
B2FChangeAddressResp::B2FChangeAddressResp(const B2FChangeAddressResp& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){from._impl_._has_bits_}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.seqnum_){}
    , decltype(_impl_.shipid_){}
    , decltype(_impl_.result_){}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&_impl_.seqnum_, &from._impl_.seqnum_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.result_) -
    reinterpret_cast<char*>(&_impl_.seqnum_)) + sizeof(_impl_.result_));
  // @@protoc_insertion_point(copy_constructor:B2FChangeAddressResp)
}

inline void B2FChangeAddressResp::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.seqnum_){int64_t{0}}
    , decltype(_impl_.shipid_){int64_t{0}}
    , decltype(_impl_.result_){0}
  };
}

B2FChangeAddressResp::~B2FChangeAddressResp() {
  // @@protoc_insertion_point(destructor:B2FChangeAddressResp)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void B2FChangeAddressResp::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void B2FChangeAddressResp::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void B2FChangeAddressResp::Clear() {
// @@protoc_insertion_point(message_clear_start:B2FChangeAddressResp)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x00000007u) {
    ::memset(&_impl_.seqnum_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&_impl_.result_) -
        reinterpret_cast<char*>(&_impl_.seqnum_)) + sizeof(_impl_.result_));
  }
  _impl_._has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* B2FChangeAddressResp::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // required int64 seqnum = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _Internal::set_has_seqnum(&has_bits);
          _impl_.seqnum_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // required int64 shipid = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          _Internal::set_has_shipid(&has_bits);
          _impl_.shipid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // required int32 result = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 24)) {
          _Internal::set_has_result(&has_bits);
          _impl_.result_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
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
  _impl_._has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* B2FChangeAddressResp::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:B2FChangeAddressResp)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  // required int64 seqnum = 1;
  if (cached_has_bits & 0x00000001u) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt64ToArray(1, this->_internal_seqnum(), target);
  }

  // required int64 shipid = 2;
  if (cached_has_bits & 0x00000002u) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt64ToArray(2, this->_internal_shipid(), target);
  }

  // required int32 result = 3;
  if (cached_has_bits & 0x00000004u) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(3, this->_internal_result(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:B2FChangeAddressResp)
  return target;
}

size_t B2FChangeAddressResp::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:B2FChangeAddressResp)
  size_t total_size = 0;

  if (_internal_has_seqnum()) {
    // required int64 seqnum = 1;
    total_size += ::_pbi::WireFormatLite::Int64SizePlusOne(this->_internal_seqnum());
  }

  if (_internal_has_shipid()) {
    // required int64 shipid = 2;
    total_size += ::_pbi::WireFormatLite::Int64SizePlusOne(this->_internal_shipid());
  }

  if (_internal_has_result()) {
    // required int32 result = 3;
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_result());
  }

  return total_size;
}
size_t B2FChangeAddressResp::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:B2FChangeAddressResp)
  size_t total_size = 0;

  if (((_impl_._has_bits_[0] & 0x00000007) ^ 0x00000007) == 0) {  // All required fields are present.
    // required int64 seqnum = 1;
    total_size += ::_pbi::WireFormatLite::Int64SizePlusOne(this->_internal_seqnum());

    // required int64 shipid = 2;
    total_size += ::_pbi::WireFormatLite::Int64SizePlusOne(this->_internal_shipid());

    // required int32 result = 3;
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_result());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData B2FChangeAddressResp::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    B2FChangeAddressResp::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*B2FChangeAddressResp::GetClassData() const { return &_class_data_; }

void B2FChangeAddressResp::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<B2FChangeAddressResp *>(to)->MergeFrom(
      static_cast<const B2FChangeAddressResp &>(from));
}


void B2FChangeAddressResp::MergeFrom(const B2FChangeAddressResp& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:B2FChangeAddressResp)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._impl_._has_bits_[0];
  if (cached_has_bits & 0x00000007u) {
    if (cached_has_bits & 0x00000001u) {
      _impl_.seqnum_ = from._impl_.seqnum_;
    }
    if (cached_has_bits & 0x00000002u) {
      _impl_.shipid_ = from._impl_.shipid_;
    }
    if (cached_has_bits & 0x00000004u) {
      _impl_.result_ = from._impl_.result_;
    }
    _impl_._has_bits_[0] |= cached_has_bits;
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void B2FChangeAddressResp::CopyFrom(const B2FChangeAddressResp& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:B2FChangeAddressResp)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool B2FChangeAddressResp::IsInitialized() const {
  if (_Internal::MissingRequiredFields(_impl_._has_bits_)) return false;
  return true;
}

void B2FChangeAddressResp::InternalSwap(B2FChangeAddressResp* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_._has_bits_[0], other->_impl_._has_bits_[0]);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(B2FChangeAddressResp, _impl_.result_)
      + sizeof(B2FChangeAddressResp::_impl_.result_)
      - PROTOBUF_FIELD_OFFSET(B2FChangeAddressResp, _impl_.seqnum_)>(
          reinterpret_cast<char*>(&_impl_.seqnum_),
          reinterpret_cast<char*>(&other->_impl_.seqnum_));
}

::PROTOBUF_NAMESPACE_ID::Metadata B2FChangeAddressResp::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_frontend_2eproto_getter, &descriptor_table_frontend_2eproto_once,
      file_level_metadata_frontend_2eproto[1]);
}

// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::F2BChangeAddress*
Arena::CreateMaybeMessage< ::F2BChangeAddress >(Arena* arena) {
  return Arena::CreateMessageInternal< ::F2BChangeAddress >(arena);
}
template<> PROTOBUF_NOINLINE ::B2FChangeAddressResp*
Arena::CreateMaybeMessage< ::B2FChangeAddressResp >(Arena* arena) {
  return Arena::CreateMessageInternal< ::B2FChangeAddressResp >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
