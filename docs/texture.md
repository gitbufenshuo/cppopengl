# 生成 texture

```bash
./bintools.out texture gen ./others/resource/asset one.png 9729 9987 10497 10497
```

其中 `gen` 代表 `generate`, 就是生成。

`./others/resource/asset` 代表资源的根目录

`one.png` 代表 `asset/image/one.png` 一定存在, 生成的`texture`会引用这个文件

后面四个数字分别是

- magfilter
- minfilter
- wraps
- wrapt

生成的文件在`asset/texture`目录，名字是随机生成的:

例如： `one.png2.texture.pb`

之所以后缀是`.pb`, 是因为，这是一个`protobuf`编码的二进制文件

# 查看 texture.pb 文件内容

```bash
./bintools.out texture show ./others/resource/asset one.png2.texture.pb
```

输出结果如下:

```json
bintools Wriiten by Golang
{
    "magFilter":9729,
    "minFilter":9987,
    "wrapS":10497,
    "wrapT":10497,
    "image":"others/resource/asset/image/one.png"
}
```