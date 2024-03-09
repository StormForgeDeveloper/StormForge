// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_GENERIC_SF_FLAT_GENERIC_H_
#define FLATBUFFERS_GENERATED_GENERIC_SF_FLAT_GENERIC_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 24 &&
              FLATBUFFERS_VERSION_MINOR == 3 &&
              FLATBUFFERS_VERSION_REVISION == 7,
             "Non-compatible flatbuffers version included");

#include "LocalTypes_generated.h"

namespace SF {
namespace Flat {
namespace Generic {

struct GenericFailureCmd;
struct GenericFailureCmdBuilder;

struct GenericFailureRes;
struct GenericFailureResBuilder;

struct GenericFailureCmd FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef GenericFailureCmdBuilder Builder;
  struct Traits;
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           verifier.EndTable();
  }
};

struct GenericFailureCmdBuilder {
  typedef GenericFailureCmd Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  explicit GenericFailureCmdBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<GenericFailureCmd> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<GenericFailureCmd>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<GenericFailureCmd> CreateGenericFailureCmd(
    ::flatbuffers::FlatBufferBuilder &_fbb) {
  GenericFailureCmdBuilder builder_(_fbb);
  return builder_.Finish();
}

struct GenericFailureCmd::Traits {
  using type = GenericFailureCmd;
  static auto constexpr Create = CreateGenericFailureCmd;
  static constexpr auto name = "GenericFailureCmd";
  static constexpr auto fully_qualified_name = "SF.Flat.Generic.GenericFailureCmd";
  static constexpr size_t fields_number = 0;
  static constexpr std::array<const char *, fields_number> field_names = {};
};

struct GenericFailureRes FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef GenericFailureResBuilder Builder;
  struct Traits;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_RESULT = 4
  };
  uint32_t result() const {
    return GetField<uint32_t>(VT_RESULT, 0);
  }
  template<size_t Index>
  auto get_field() const {
         if constexpr (Index == 0) return result();
    else static_assert(Index != Index, "Invalid Field Index");
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint32_t>(verifier, VT_RESULT, 4) &&
           verifier.EndTable();
  }
};

struct GenericFailureResBuilder {
  typedef GenericFailureRes Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_result(uint32_t result) {
    fbb_.AddElement<uint32_t>(GenericFailureRes::VT_RESULT, result, 0);
  }
  explicit GenericFailureResBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<GenericFailureRes> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<GenericFailureRes>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<GenericFailureRes> CreateGenericFailureRes(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    uint32_t result = 0) {
  GenericFailureResBuilder builder_(_fbb);
  builder_.add_result(result);
  return builder_.Finish();
}

struct GenericFailureRes::Traits {
  using type = GenericFailureRes;
  static auto constexpr Create = CreateGenericFailureRes;
  static constexpr auto name = "GenericFailureRes";
  static constexpr auto fully_qualified_name = "SF.Flat.Generic.GenericFailureRes";
  static constexpr size_t fields_number = 1;
  static constexpr std::array<const char *, fields_number> field_names = {
    "result"
  };
  template<size_t Index>
  using FieldType = decltype(std::declval<type>().get_field<Index>());
};

inline const SF::Flat::Generic::GenericFailureRes *GetGenericFailureRes(const void *buf) {
  return ::flatbuffers::GetRoot<SF::Flat::Generic::GenericFailureRes>(buf);
}

inline const SF::Flat::Generic::GenericFailureRes *GetSizePrefixedGenericFailureRes(const void *buf) {
  return ::flatbuffers::GetSizePrefixedRoot<SF::Flat::Generic::GenericFailureRes>(buf);
}

inline bool VerifyGenericFailureResBuffer(
    ::flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<SF::Flat::Generic::GenericFailureRes>(nullptr);
}

inline bool VerifySizePrefixedGenericFailureResBuffer(
    ::flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<SF::Flat::Generic::GenericFailureRes>(nullptr);
}

inline void FinishGenericFailureResBuffer(
    ::flatbuffers::FlatBufferBuilder &fbb,
    ::flatbuffers::Offset<SF::Flat::Generic::GenericFailureRes> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedGenericFailureResBuffer(
    ::flatbuffers::FlatBufferBuilder &fbb,
    ::flatbuffers::Offset<SF::Flat::Generic::GenericFailureRes> root) {
  fbb.FinishSizePrefixed(root);
}

}  // namespace Generic
}  // namespace Flat
}  // namespace SF

#endif  // FLATBUFFERS_GENERATED_GENERIC_SF_FLAT_GENERIC_H_
