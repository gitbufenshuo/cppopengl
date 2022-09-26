// Code generated by protoc-gen-go. DO NOT EDIT.
// versions:
// 	protoc-gen-go v1.26.0
// 	protoc        v3.21.5
// source: mc/comm/pbnode.proto

package comm

import (
	protoreflect "google.golang.org/protobuf/reflect/protoreflect"
	protoimpl "google.golang.org/protobuf/runtime/protoimpl"
	reflect "reflect"
	sync "sync"
)

const (
	// Verify that this generated code is sufficiently up-to-date.
	_ = protoimpl.EnforceVersion(20 - protoimpl.MinVersion)
	// Verify that runtime/protoimpl is sufficiently up-to-date.
	_ = protoimpl.EnforceVersion(protoimpl.MaxVersion - 20)
)

type PBVec4 struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	W float32 `protobuf:"fixed32,1,opt,name=w,proto3" json:"w,omitempty"`
	X float32 `protobuf:"fixed32,2,opt,name=x,proto3" json:"x,omitempty"`
	Y float32 `protobuf:"fixed32,3,opt,name=y,proto3" json:"y,omitempty"`
	Z float32 `protobuf:"fixed32,4,opt,name=z,proto3" json:"z,omitempty"`
}

func (x *PBVec4) Reset() {
	*x = PBVec4{}
	if protoimpl.UnsafeEnabled {
		mi := &file_mc_comm_pbnode_proto_msgTypes[0]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *PBVec4) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*PBVec4) ProtoMessage() {}

func (x *PBVec4) ProtoReflect() protoreflect.Message {
	mi := &file_mc_comm_pbnode_proto_msgTypes[0]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use PBVec4.ProtoReflect.Descriptor instead.
func (*PBVec4) Descriptor() ([]byte, []int) {
	return file_mc_comm_pbnode_proto_rawDescGZIP(), []int{0}
}

func (x *PBVec4) GetW() float32 {
	if x != nil {
		return x.W
	}
	return 0
}

func (x *PBVec4) GetX() float32 {
	if x != nil {
		return x.X
	}
	return 0
}

func (x *PBVec4) GetY() float32 {
	if x != nil {
		return x.Y
	}
	return 0
}

func (x *PBVec4) GetZ() float32 {
	if x != nil {
		return x.Z
	}
	return 0
}

type PBTransform struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	Translate *PBVec4 `protobuf:"bytes,1,opt,name=translate,proto3" json:"translate,omitempty"`
	Rotation  *PBVec4 `protobuf:"bytes,2,opt,name=rotation,proto3" json:"rotation,omitempty"`
}

func (x *PBTransform) Reset() {
	*x = PBTransform{}
	if protoimpl.UnsafeEnabled {
		mi := &file_mc_comm_pbnode_proto_msgTypes[1]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *PBTransform) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*PBTransform) ProtoMessage() {}

func (x *PBTransform) ProtoReflect() protoreflect.Message {
	mi := &file_mc_comm_pbnode_proto_msgTypes[1]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use PBTransform.ProtoReflect.Descriptor instead.
func (*PBTransform) Descriptor() ([]byte, []int) {
	return file_mc_comm_pbnode_proto_rawDescGZIP(), []int{1}
}

func (x *PBTransform) GetTranslate() *PBVec4 {
	if x != nil {
		return x.Translate
	}
	return nil
}

func (x *PBTransform) GetRotation() *PBVec4 {
	if x != nil {
		return x.Rotation
	}
	return nil
}

type PBNode struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	Transform    *PBTransform `protobuf:"bytes,1,opt,name=transform,proto3" json:"transform,omitempty"`
	ActLogicList []string     `protobuf:"bytes,2,rep,name=act_logic_list,json=actLogicList,proto3" json:"act_logic_list,omitempty"`
	ModelList    []string     `protobuf:"bytes,3,rep,name=model_list,json=modelList,proto3" json:"model_list,omitempty"` // 一个 node 会有多个 mesh
	Material     string       `protobuf:"bytes,4,opt,name=material,proto3" json:"material,omitempty"`
	SubList      []*PBNode    `protobuf:"bytes,5,rep,name=sub_list,json=subList,proto3" json:"sub_list,omitempty"` // 所有的子节点
}

func (x *PBNode) Reset() {
	*x = PBNode{}
	if protoimpl.UnsafeEnabled {
		mi := &file_mc_comm_pbnode_proto_msgTypes[2]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *PBNode) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*PBNode) ProtoMessage() {}

func (x *PBNode) ProtoReflect() protoreflect.Message {
	mi := &file_mc_comm_pbnode_proto_msgTypes[2]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use PBNode.ProtoReflect.Descriptor instead.
func (*PBNode) Descriptor() ([]byte, []int) {
	return file_mc_comm_pbnode_proto_rawDescGZIP(), []int{2}
}

func (x *PBNode) GetTransform() *PBTransform {
	if x != nil {
		return x.Transform
	}
	return nil
}

func (x *PBNode) GetActLogicList() []string {
	if x != nil {
		return x.ActLogicList
	}
	return nil
}

func (x *PBNode) GetModelList() []string {
	if x != nil {
		return x.ModelList
	}
	return nil
}

func (x *PBNode) GetMaterial() string {
	if x != nil {
		return x.Material
	}
	return ""
}

func (x *PBNode) GetSubList() []*PBNode {
	if x != nil {
		return x.SubList
	}
	return nil
}

type PBScene struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	RootList []*PBNode `protobuf:"bytes,1,rep,name=root_list,json=rootList,proto3" json:"root_list,omitempty"` // 所有根节点
}

func (x *PBScene) Reset() {
	*x = PBScene{}
	if protoimpl.UnsafeEnabled {
		mi := &file_mc_comm_pbnode_proto_msgTypes[3]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *PBScene) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*PBScene) ProtoMessage() {}

func (x *PBScene) ProtoReflect() protoreflect.Message {
	mi := &file_mc_comm_pbnode_proto_msgTypes[3]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use PBScene.ProtoReflect.Descriptor instead.
func (*PBScene) Descriptor() ([]byte, []int) {
	return file_mc_comm_pbnode_proto_rawDescGZIP(), []int{3}
}

func (x *PBScene) GetRootList() []*PBNode {
	if x != nil {
		return x.RootList
	}
	return nil
}

type PBVec3 struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	W float32 `protobuf:"fixed32,1,opt,name=w,proto3" json:"w,omitempty"`
	X float32 `protobuf:"fixed32,2,opt,name=x,proto3" json:"x,omitempty"`
	Y float32 `protobuf:"fixed32,3,opt,name=y,proto3" json:"y,omitempty"`
}

func (x *PBVec3) Reset() {
	*x = PBVec3{}
	if protoimpl.UnsafeEnabled {
		mi := &file_mc_comm_pbnode_proto_msgTypes[4]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *PBVec3) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*PBVec3) ProtoMessage() {}

func (x *PBVec3) ProtoReflect() protoreflect.Message {
	mi := &file_mc_comm_pbnode_proto_msgTypes[4]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use PBVec3.ProtoReflect.Descriptor instead.
func (*PBVec3) Descriptor() ([]byte, []int) {
	return file_mc_comm_pbnode_proto_rawDescGZIP(), []int{4}
}

func (x *PBVec3) GetW() float32 {
	if x != nil {
		return x.W
	}
	return 0
}

func (x *PBVec3) GetX() float32 {
	if x != nil {
		return x.X
	}
	return 0
}

func (x *PBVec3) GetY() float32 {
	if x != nil {
		return x.Y
	}
	return 0
}

type PBLight struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	Pos         *PBVec3 `protobuf:"bytes,1,opt,name=pos,proto3" json:"pos,omitempty"`                 // 光源位置， 对于 direction light， 此项无意义
	Forward     *PBVec3 `protobuf:"bytes,2,opt,name=forward,proto3" json:"forward,omitempty"`         // 光的发射方向
	Color       *PBVec3 `protobuf:"bytes,3,opt,name=color,proto3" json:"color,omitempty"`             // 光源颜色
	Attenuation *PBVec3 `protobuf:"bytes,4,opt,name=attenuation,proto3" json:"attenuation,omitempty"` // 光源衰减
	Kind        int32   `protobuf:"varint,5,opt,name=kind,proto3" json:"kind,omitempty"`              // 光源种类 direction, point, spot
}

func (x *PBLight) Reset() {
	*x = PBLight{}
	if protoimpl.UnsafeEnabled {
		mi := &file_mc_comm_pbnode_proto_msgTypes[5]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *PBLight) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*PBLight) ProtoMessage() {}

func (x *PBLight) ProtoReflect() protoreflect.Message {
	mi := &file_mc_comm_pbnode_proto_msgTypes[5]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use PBLight.ProtoReflect.Descriptor instead.
func (*PBLight) Descriptor() ([]byte, []int) {
	return file_mc_comm_pbnode_proto_rawDescGZIP(), []int{5}
}

func (x *PBLight) GetPos() *PBVec3 {
	if x != nil {
		return x.Pos
	}
	return nil
}

func (x *PBLight) GetForward() *PBVec3 {
	if x != nil {
		return x.Forward
	}
	return nil
}

func (x *PBLight) GetColor() *PBVec3 {
	if x != nil {
		return x.Color
	}
	return nil
}

func (x *PBLight) GetAttenuation() *PBVec3 {
	if x != nil {
		return x.Attenuation
	}
	return nil
}

func (x *PBLight) GetKind() int32 {
	if x != nil {
		return x.Kind
	}
	return 0
}

var File_mc_comm_pbnode_proto protoreflect.FileDescriptor

var file_mc_comm_pbnode_proto_rawDesc = []byte{
	0x0a, 0x14, 0x6d, 0x63, 0x2f, 0x63, 0x6f, 0x6d, 0x6d, 0x2f, 0x70, 0x62, 0x6e, 0x6f, 0x64, 0x65,
	0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x12, 0x07, 0x6d, 0x63, 0x2e, 0x63, 0x6f, 0x6d, 0x6d, 0x22,
	0x40, 0x0a, 0x06, 0x50, 0x42, 0x56, 0x65, 0x63, 0x34, 0x12, 0x0c, 0x0a, 0x01, 0x77, 0x18, 0x01,
	0x20, 0x01, 0x28, 0x02, 0x52, 0x01, 0x77, 0x12, 0x0c, 0x0a, 0x01, 0x78, 0x18, 0x02, 0x20, 0x01,
	0x28, 0x02, 0x52, 0x01, 0x78, 0x12, 0x0c, 0x0a, 0x01, 0x79, 0x18, 0x03, 0x20, 0x01, 0x28, 0x02,
	0x52, 0x01, 0x79, 0x12, 0x0c, 0x0a, 0x01, 0x7a, 0x18, 0x04, 0x20, 0x01, 0x28, 0x02, 0x52, 0x01,
	0x7a, 0x22, 0x69, 0x0a, 0x0b, 0x50, 0x42, 0x54, 0x72, 0x61, 0x6e, 0x73, 0x66, 0x6f, 0x72, 0x6d,
	0x12, 0x2d, 0x0a, 0x09, 0x74, 0x72, 0x61, 0x6e, 0x73, 0x6c, 0x61, 0x74, 0x65, 0x18, 0x01, 0x20,
	0x01, 0x28, 0x0b, 0x32, 0x0f, 0x2e, 0x6d, 0x63, 0x2e, 0x63, 0x6f, 0x6d, 0x6d, 0x2e, 0x50, 0x42,
	0x56, 0x65, 0x63, 0x34, 0x52, 0x09, 0x74, 0x72, 0x61, 0x6e, 0x73, 0x6c, 0x61, 0x74, 0x65, 0x12,
	0x2b, 0x0a, 0x08, 0x72, 0x6f, 0x74, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x18, 0x02, 0x20, 0x01, 0x28,
	0x0b, 0x32, 0x0f, 0x2e, 0x6d, 0x63, 0x2e, 0x63, 0x6f, 0x6d, 0x6d, 0x2e, 0x50, 0x42, 0x56, 0x65,
	0x63, 0x34, 0x52, 0x08, 0x72, 0x6f, 0x74, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x22, 0xc9, 0x01, 0x0a,
	0x06, 0x50, 0x42, 0x4e, 0x6f, 0x64, 0x65, 0x12, 0x32, 0x0a, 0x09, 0x74, 0x72, 0x61, 0x6e, 0x73,
	0x66, 0x6f, 0x72, 0x6d, 0x18, 0x01, 0x20, 0x01, 0x28, 0x0b, 0x32, 0x14, 0x2e, 0x6d, 0x63, 0x2e,
	0x63, 0x6f, 0x6d, 0x6d, 0x2e, 0x50, 0x42, 0x54, 0x72, 0x61, 0x6e, 0x73, 0x66, 0x6f, 0x72, 0x6d,
	0x52, 0x09, 0x74, 0x72, 0x61, 0x6e, 0x73, 0x66, 0x6f, 0x72, 0x6d, 0x12, 0x24, 0x0a, 0x0e, 0x61,
	0x63, 0x74, 0x5f, 0x6c, 0x6f, 0x67, 0x69, 0x63, 0x5f, 0x6c, 0x69, 0x73, 0x74, 0x18, 0x02, 0x20,
	0x03, 0x28, 0x09, 0x52, 0x0c, 0x61, 0x63, 0x74, 0x4c, 0x6f, 0x67, 0x69, 0x63, 0x4c, 0x69, 0x73,
	0x74, 0x12, 0x1d, 0x0a, 0x0a, 0x6d, 0x6f, 0x64, 0x65, 0x6c, 0x5f, 0x6c, 0x69, 0x73, 0x74, 0x18,
	0x03, 0x20, 0x03, 0x28, 0x09, 0x52, 0x09, 0x6d, 0x6f, 0x64, 0x65, 0x6c, 0x4c, 0x69, 0x73, 0x74,
	0x12, 0x1a, 0x0a, 0x08, 0x6d, 0x61, 0x74, 0x65, 0x72, 0x69, 0x61, 0x6c, 0x18, 0x04, 0x20, 0x01,
	0x28, 0x09, 0x52, 0x08, 0x6d, 0x61, 0x74, 0x65, 0x72, 0x69, 0x61, 0x6c, 0x12, 0x2a, 0x0a, 0x08,
	0x73, 0x75, 0x62, 0x5f, 0x6c, 0x69, 0x73, 0x74, 0x18, 0x05, 0x20, 0x03, 0x28, 0x0b, 0x32, 0x0f,
	0x2e, 0x6d, 0x63, 0x2e, 0x63, 0x6f, 0x6d, 0x6d, 0x2e, 0x50, 0x42, 0x4e, 0x6f, 0x64, 0x65, 0x52,
	0x07, 0x73, 0x75, 0x62, 0x4c, 0x69, 0x73, 0x74, 0x22, 0x37, 0x0a, 0x07, 0x50, 0x42, 0x53, 0x63,
	0x65, 0x6e, 0x65, 0x12, 0x2c, 0x0a, 0x09, 0x72, 0x6f, 0x6f, 0x74, 0x5f, 0x6c, 0x69, 0x73, 0x74,
	0x18, 0x01, 0x20, 0x03, 0x28, 0x0b, 0x32, 0x0f, 0x2e, 0x6d, 0x63, 0x2e, 0x63, 0x6f, 0x6d, 0x6d,
	0x2e, 0x50, 0x42, 0x4e, 0x6f, 0x64, 0x65, 0x52, 0x08, 0x72, 0x6f, 0x6f, 0x74, 0x4c, 0x69, 0x73,
	0x74, 0x22, 0x32, 0x0a, 0x06, 0x50, 0x42, 0x56, 0x65, 0x63, 0x33, 0x12, 0x0c, 0x0a, 0x01, 0x77,
	0x18, 0x01, 0x20, 0x01, 0x28, 0x02, 0x52, 0x01, 0x77, 0x12, 0x0c, 0x0a, 0x01, 0x78, 0x18, 0x02,
	0x20, 0x01, 0x28, 0x02, 0x52, 0x01, 0x78, 0x12, 0x0c, 0x0a, 0x01, 0x79, 0x18, 0x03, 0x20, 0x01,
	0x28, 0x02, 0x52, 0x01, 0x79, 0x22, 0xc5, 0x01, 0x0a, 0x07, 0x50, 0x42, 0x4c, 0x69, 0x67, 0x68,
	0x74, 0x12, 0x21, 0x0a, 0x03, 0x70, 0x6f, 0x73, 0x18, 0x01, 0x20, 0x01, 0x28, 0x0b, 0x32, 0x0f,
	0x2e, 0x6d, 0x63, 0x2e, 0x63, 0x6f, 0x6d, 0x6d, 0x2e, 0x50, 0x42, 0x56, 0x65, 0x63, 0x33, 0x52,
	0x03, 0x70, 0x6f, 0x73, 0x12, 0x29, 0x0a, 0x07, 0x66, 0x6f, 0x72, 0x77, 0x61, 0x72, 0x64, 0x18,
	0x02, 0x20, 0x01, 0x28, 0x0b, 0x32, 0x0f, 0x2e, 0x6d, 0x63, 0x2e, 0x63, 0x6f, 0x6d, 0x6d, 0x2e,
	0x50, 0x42, 0x56, 0x65, 0x63, 0x33, 0x52, 0x07, 0x66, 0x6f, 0x72, 0x77, 0x61, 0x72, 0x64, 0x12,
	0x25, 0x0a, 0x05, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x18, 0x03, 0x20, 0x01, 0x28, 0x0b, 0x32, 0x0f,
	0x2e, 0x6d, 0x63, 0x2e, 0x63, 0x6f, 0x6d, 0x6d, 0x2e, 0x50, 0x42, 0x56, 0x65, 0x63, 0x33, 0x52,
	0x05, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x12, 0x31, 0x0a, 0x0b, 0x61, 0x74, 0x74, 0x65, 0x6e, 0x75,
	0x61, 0x74, 0x69, 0x6f, 0x6e, 0x18, 0x04, 0x20, 0x01, 0x28, 0x0b, 0x32, 0x0f, 0x2e, 0x6d, 0x63,
	0x2e, 0x63, 0x6f, 0x6d, 0x6d, 0x2e, 0x50, 0x42, 0x56, 0x65, 0x63, 0x33, 0x52, 0x0b, 0x61, 0x74,
	0x74, 0x65, 0x6e, 0x75, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x12, 0x12, 0x0a, 0x04, 0x6b, 0x69, 0x6e,
	0x64, 0x18, 0x05, 0x20, 0x01, 0x28, 0x05, 0x52, 0x04, 0x6b, 0x69, 0x6e, 0x64, 0x42, 0x09, 0x5a,
	0x07, 0x6d, 0x63, 0x2f, 0x63, 0x6f, 0x6d, 0x6d, 0x62, 0x06, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x33,
}

var (
	file_mc_comm_pbnode_proto_rawDescOnce sync.Once
	file_mc_comm_pbnode_proto_rawDescData = file_mc_comm_pbnode_proto_rawDesc
)

func file_mc_comm_pbnode_proto_rawDescGZIP() []byte {
	file_mc_comm_pbnode_proto_rawDescOnce.Do(func() {
		file_mc_comm_pbnode_proto_rawDescData = protoimpl.X.CompressGZIP(file_mc_comm_pbnode_proto_rawDescData)
	})
	return file_mc_comm_pbnode_proto_rawDescData
}

var file_mc_comm_pbnode_proto_msgTypes = make([]protoimpl.MessageInfo, 6)
var file_mc_comm_pbnode_proto_goTypes = []interface{}{
	(*PBVec4)(nil),      // 0: mc.comm.PBVec4
	(*PBTransform)(nil), // 1: mc.comm.PBTransform
	(*PBNode)(nil),      // 2: mc.comm.PBNode
	(*PBScene)(nil),     // 3: mc.comm.PBScene
	(*PBVec3)(nil),      // 4: mc.comm.PBVec3
	(*PBLight)(nil),     // 5: mc.comm.PBLight
}
var file_mc_comm_pbnode_proto_depIdxs = []int32{
	0, // 0: mc.comm.PBTransform.translate:type_name -> mc.comm.PBVec4
	0, // 1: mc.comm.PBTransform.rotation:type_name -> mc.comm.PBVec4
	1, // 2: mc.comm.PBNode.transform:type_name -> mc.comm.PBTransform
	2, // 3: mc.comm.PBNode.sub_list:type_name -> mc.comm.PBNode
	2, // 4: mc.comm.PBScene.root_list:type_name -> mc.comm.PBNode
	4, // 5: mc.comm.PBLight.pos:type_name -> mc.comm.PBVec3
	4, // 6: mc.comm.PBLight.forward:type_name -> mc.comm.PBVec3
	4, // 7: mc.comm.PBLight.color:type_name -> mc.comm.PBVec3
	4, // 8: mc.comm.PBLight.attenuation:type_name -> mc.comm.PBVec3
	9, // [9:9] is the sub-list for method output_type
	9, // [9:9] is the sub-list for method input_type
	9, // [9:9] is the sub-list for extension type_name
	9, // [9:9] is the sub-list for extension extendee
	0, // [0:9] is the sub-list for field type_name
}

func init() { file_mc_comm_pbnode_proto_init() }
func file_mc_comm_pbnode_proto_init() {
	if File_mc_comm_pbnode_proto != nil {
		return
	}
	if !protoimpl.UnsafeEnabled {
		file_mc_comm_pbnode_proto_msgTypes[0].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*PBVec4); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
		file_mc_comm_pbnode_proto_msgTypes[1].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*PBTransform); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
		file_mc_comm_pbnode_proto_msgTypes[2].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*PBNode); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
		file_mc_comm_pbnode_proto_msgTypes[3].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*PBScene); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
		file_mc_comm_pbnode_proto_msgTypes[4].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*PBVec3); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
		file_mc_comm_pbnode_proto_msgTypes[5].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*PBLight); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
	}
	type x struct{}
	out := protoimpl.TypeBuilder{
		File: protoimpl.DescBuilder{
			GoPackagePath: reflect.TypeOf(x{}).PkgPath(),
			RawDescriptor: file_mc_comm_pbnode_proto_rawDesc,
			NumEnums:      0,
			NumMessages:   6,
			NumExtensions: 0,
			NumServices:   0,
		},
		GoTypes:           file_mc_comm_pbnode_proto_goTypes,
		DependencyIndexes: file_mc_comm_pbnode_proto_depIdxs,
		MessageInfos:      file_mc_comm_pbnode_proto_msgTypes,
	}.Build()
	File_mc_comm_pbnode_proto = out.File
	file_mc_comm_pbnode_proto_rawDesc = nil
	file_mc_comm_pbnode_proto_goTypes = nil
	file_mc_comm_pbnode_proto_depIdxs = nil
}
