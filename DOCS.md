This page will serve as the home of the documentation of all the public facing API functions within SoGL.
SoGL is not without all visual aid, as the [examples directory](https://github.com/zafflin/SoGL/tree/master/examples) includes a handful of useful and experimental scenes and demos you can learn from in a more "on-the-go" fashion. Feel free to check it out at anytime, or open an issue should you encounter any problems.
<br>
<br>

### Modules Documented

[ _**Core**_:
    | [sogl.h](https://github.com/zafflin/SoGL/wiki/SoGL-API-Docs#--soglh) | 
    [smath.h](https://github.com/zafflin/SoGL/wiki/SoGL-API-Docs#--smathh) | 
    [shapes.h](https://github.com/zafflin/SoGL/wiki/SoGL-API-Docs#--shapesh) | 
    [sevent.h](https://github.com/zafflin/SoGL/wiki/SoGL-API-Docs#--seventh)
]

[ _**Context**_:
    | [store.h](https://github.com/zafflin/SoGL/wiki/SoGL-API-Docs#--ctxstoreh) | 
    [render.h](https://github.com/zafflin/SoGL/wiki/SoGL-API-Docs#--ctxrenderh) | 
    [generator.h](https://github.com/zafflin/SoGL/wiki/SoGL-API-Docs#--ctxgeneratorh) | 
    [constructor.h](https://github.com/zafflin/SoGL/wiki/SoGL-API-Docs#--ctxconstructorh)
]
<br>
<br>

## - sogl.h
```c
void soglInit(void)
```
**Description**: Configures default settings and state for the global SOGL structure `SGcontext` and populates general system info fields.

**Parameters**:
- `void`

**Returns**: `void`
<br>
<br>

```c
void sgContextDebug(const SGcontext *ctx)
```
**Description**: A function to print debug information for the global SOGL structure `SGcontext` to the standard output.

**Parameters**:
- `SGcontext* ctx`

**Returns**: `void`
<br>
<br>

## - smath.h
#### ( SGvec2, SGvec3, SGvec4 ) Operations 

```c
void sgGetVec3Str(const SGvec3* vec)
```
( SGvec2 and SGvec4 variants available. )

**Description**: Converts the SGvec3 vector into a string representation.

**Parameters**:
- `const SGvec3* vec`: Pointer to the vector to be converted.

**Returns**: `void`

---

```c
void sgScalarVec3a(SGvec3* v1, u32 scalar)
```
( SGvec2 and SGvec4 variants available. )

**Description**: Adds a scalar value to each component of the vector.

**Parameters**:
- `SGvec3* v1`: Pointer to the vector to be modified.
- `u32 scalar`: The scalar value to add.

**Returns**: `void`

---

```c
void sgScalarVec3s(SGvec3* v1, u32 scalar)
```
( SGvec2 and SGvec4 variants available. )

**Description**: Subtracts a scalar value from each component of the vector.

**Parameters**:
- `SGvec3* v1`: Pointer to the vector to be modified.
- `u32 scalar`: The scalar value to subtract.

**Returns**: `void`

---

```c
void sgNegVec3(SGvec3* v1)
```
( SGvec2 and SGvec4 variants available. )

**Description**: Negates each component of the vector.

**Parameters**:
- `SGvec3* v1`: Pointer to the vector to be negated.

**Returns**: `void`

---

```c
void sgAddVec3(SGvec3* v1, SGvec3 v2)
```
( SGvec2 and SGvec4 variants available. )

**Description**: Adds two vectors component-wise and stores the result in the first vector.

**Parameters**:
- `SGvec3* v1`: Pointer to the first vector and storage for the result.
- `SGvec3 v2`: The second vector to add.

**Returns**: `void`

---

```c
void sgSubVec3(SGvec3* v1, SGvec3 v2)
```
( SGvec2 and SGvec4 variants available. )

**Description**: Subtracts the second vector from the first vector component-wise and stores the result in the first vector.

**Parameters**:
- `SGvec3* v1`: Pointer to the first vector and storage for the result.
- `SGvec3 v2`: The second vector to subtract.

**Returns**: `void`

---

```c
f32 sgLenVec3(SGvec3 vec)
```
( SGvec2 and SGvec4 variants available. )

**Description**: Calculates the length (magnitude) of the vector.

**Parameters**:
- `SGvec3 vec`: The vector whose length is to be calculated.

**Returns**: `f32` - The length of the vector.

---

```c
void sgNormVec3(SGvec3* v1)
```
( SGvec2 and SGvec4 variants available. )

**Description**: Normalizes the vector, making its length equal to 1 while maintaining its direction.

**Parameters**:
- `SGvec3* v1`: Pointer to the vector to be normalized.

**Returns**: `void`

---

```c
f32 sgDotVec3(SGvec3 v1, SGvec3 v2)
```
( SGvec2 and SGvec4 variants available. )

**Description**: Calculates the dot product of two vectors. 

**Parameters**:
- `SGvec3 v1`: The first vector.
- `SGvec3 v2`: The second vector.

**Returns**: `f32` - The dot product of the two vectors.

---

```c
void sgCrossVec3(SGvec3* v1, SGvec3 v2)
```
**Description**: Calculates the cross product of two vectors and stores the result in the first vector.

**Parameters**:
- `SGvec3* v1`: Pointer to the first vector and storage for the result.
- `SGvec3 v2`: The second vector.

**Returns**: `void`

---

```c
void sgGetMat4Str(const SGmat4* mat)
```
**Description**: Converts the SGmat4 matrix into a string representation.

**Parameters**:
- `const SGmat4* mat`: Pointer to the matrix to be converted.

**Returns**: `void`

---

#### ( SGmat4 ) Operations

```c
SGmat4 sgIdentity(void)
```
**Description**: Creates and returns an identity matrix.

**Parameters**: None.

**Returns**: `SGmat4` - The identity matrix.

---

```c
void sgScalarMat4(SGmat4* m1, u32 scalar)
```
**Description**: Multiplies each component of the matrix by a scalar value.

**Parameters**:
- `SGmat4* m1`: Pointer to the matrix to be modified.
- `u32 scalar`: The scalar value to multiply.

**Returns**: `void`

---

```c
void sgAddMat4(SGmat4* m1, SGmat4 m2)
```
**Description**: Adds two matrices component-wise and stores the result in the first matrix.

**Parameters**:
- `SGmat4* m1`: Pointer to the first matrix and storage for the result.
- `SGmat4 m2`: The second matrix to add.

**Returns**: `void`

---

```c
void sgSubMat4(SGmat4* m1, SGmat4 m2)
```
**Description**: Subtracts the second matrix from the first matrix component-wise and stores the result in the first matrix.

**Parameters**:
- `SGmat4* m1`: Pointer to the first matrix and storage for the result.
- `SGmat4 m2`: The second matrix to subtract.

**Returns**: `void`

---

```c
void sgMulMat4(SGmat4* result, SGmat4 m1, SGmat4 m2)
```
**Description**: Multiplies two matrices and stores the result in the result matrix.

**Parameters**:
- `SGmat4* result`: Pointer to the matrix to store the result.
- `SGmat4 m1`: The first matrix.
- `SGmat4 m2`: The second matrix.

**Returns**: `void`

---

```c
void sgScaleMat4(SGmat4* m1, SGvec3 vec)
```
**Description**: Applies a scaling transformation to the matrix using the specified vector.

**Parameters**:
- `SGmat4* m1`: Pointer to the matrix to be scaled.
- `SGvec3 vec`: The scaling vector.

**Returns**: `void`

---

```c
void sgTransMat4(SGmat4* m1, SGvec3 vec)
```
**Description**: Applies a translation transformation to the matrix using the specified vector.

**Parameters**:
- `SGmat4* m1`: Pointer to the matrix to be translated.
- `SGvec3 vec`: The translation vector.

**Returns**: `void`

---

```c
void sgRotXMat4(SGmat4* m1, float angle)
```
**Description**: Applies a rotation around the X-axis to the matrix using the specified angle.

**Parameters**:
- `SGmat4* m1`: Pointer to the matrix to be rotated.
- `float angle`: The rotation angle in radians.

**Returns**: `void`

---

```c
void sgRotYMat4(SGmat4* m1, float angle)
```
**Description**: Applies a rotation around the Y-axis to the matrix using the specified angle.

**Parameters**:
- `SGmat4* m1`: Pointer to the matrix to be rotated.
- `float angle`: The rotation angle in radians.

**Returns**: `void`

---

```c
void sgRotZMat4(SGmat4* m1, float angle)
```
**Description**: Applies a rotation around the Z-axis to the matrix using the specified angle.

**Parameters**:
- `SGmat4* m1`: Pointer to the matrix to be rotated.
- `float angle`: The rotation angle in radians.

**Returns**: `void`

---

```c
void sgRotMat4(SGmat4* result, float angleX, float angleY, float angleZ)
```
**Description**: Applies a rotation around all three axes (X, Y, Z) to the matrix using the specified angles.

**Parameters**:
- `SGmat4

* result`: Pointer to the matrix to store the result.
- `float angleX`: The rotation angle around the X-axis in radians.
- `float angleY`: The rotation angle around the Y-axis in radians.
- `float angleZ`: The rotation angle around the Z-axis in radians.

**Returns**: `void`
<br>
<br>

## - shapes.h
```c
void sgInitShapes(void)
```
**Description**: Initializes predefined shapes (quad and triangle) for rendering. This function sets up vertex data for these shapes and stores them in handles for efficient rendering.

**Parameters**:
- `void`

**Returns**: `void`
<br>
<br>

```c
SGdrawcall* sgDrawQuad(SGhandle* thandle, SGhandle* shandle, const SGhandle* uniforms, u32 nuniforms)
```
**Description**: Generates a draw call for rendering a quad. If the `SG_PREGENERATE` flag is set, it uses a pre-generated quad handle. Otherwise, it generates the quad vertices and texture coordinates on the fly.

**Parameters**:
- `SGhandle* thandle`: Texture handle to be used in the draw call.
- `SGhandle* shandle`: Shader handle to be used in the draw call.
- `const SGhandle* uniforms`: Array of uniform handles to be used in the draw call.
- `u32 nuniforms`: Number of uniform handles.

**Returns**: `SGdrawcall*` - Pointer to the generated draw call.
<br>
<br>

```c
SGdrawcall* sgDrawTriangle(SGhandle* thandle, SGhandle* shandle, const SGhandle* uniforms, u32 nuniforms)
```
**Description**: Generates a draw call for rendering a triangle. If the `SG_PREGENERATE` flag is set, it uses a pre-generated triangle handle. Otherwise, it generates the triangle vertices and texture coordinates on the fly.

**Parameters**:
- `SGhandle* thandle`: Texture handle to be used in the draw call.
- `SGhandle* shandle`: Shader handle to be used in the draw call.
- `const SGhandle* uniforms`: Array of uniform handles to be used in the draw call.
- `u32 nuniforms`: Number of uniform handles.

**Returns**: `SGdrawcall*` - Pointer to the generated draw call.
<br>
<br>

## - sevent.h
( NOT YET IMPLEMENTED )
<br>
<br>

## - ctx/generator.h
```c
SGhandle sgGenHandle(u32 htype, ...)
```
**Description**: Hook directly into the generator context to return a handle of the user-specified resource type.

**Parameters**:
- `unsigned int htype`: The user specified resource type hint.
- `...`: variadic arguments to be passed to the corresponding sgGenx function.
    - These are the possible va_args based on a given resource type:
        <br>
        <br>
        
        ``` SG_MESH ```
        ```c
            float* verts = va_arg(args, float*);
            unsigned int nverts = va_arg(args, unsigned int);
            float* texcoords = va_arg(args, float*);
            unsigned int ntexcoords = va_arg(args, unsigned int);
        ```
        <br>

        ``` SG_UNIFORM ```
        ```c
            char* name = va_arg(args, char*);
            unsigned int type = va_arg(args, unsigned int);
            SGhandle* shandle = va_arg(args, SGhandle*);
        ```
        <br>

        ``` SG_HANDLE ```
        ```c
            const char* vert_src = va_arg(args, const char*);
            const char* frag_src = va_arg(args, const char*);
        ```
        <br>

        ``` SG_TEXTURE ```
        ```c
            char* src = va_arg(args, char*);
            unsigned int format = va_arg(args, unsigned int);
        ```

**Returns**: `SGhandle` containing relevant configuration, and error data.

<br>
<br>

## - ctx/constructor.h

```c
void* sgBindConstructor(SGhandle* target)
```

**Description**: 
Binds a handle to the constructor context, allowing the system to configure and construct resources based on the type of the handle. This function sets up the internal context and, depending on the handle type, calls the appropriate constructor function to initialize the resource.

**Parameters**:
- `SGhandle* target`: A pointer to the handle to be bound to the constructor context. If `NULL`, the current binding is unbound.

**Returns**: `void*`
<br>
<br>

## - ctx/store.h
```c
void sgInitResourceBlock(ResourceType type)
```
**Description**: 
Initializes and configures the resource block for a specified resource type within the global `SGcontext`. This function sets up the necessary settings and state for managing resources of the given type.

**Parameters**:
- `ResourceType type`: The type of resource block to initialize (e.g., `SG_MESH`, `SG_SHADER`, `SG_TEXTURE`, `SG_UNIFORM`).

**Returns**: `void`
<br>
<br>

```c
void sgStoreMesh(SGhandle* handle)
```
**Description**: 
Stores the mesh data associated with the provided handle into the global `SGcontext`. This function ensures the mesh resource is properly stored and accessible for rendering operations.

**Parameters**:
- `SGhandle* handle`: A pointer to the handle containing the mesh data to be stored.

**Returns**: `void`
<br>
<br>

```c
void sgStoreShader(SGhandle* handle)
```
**Description**: 
Stores the shader data associated with the provided handle into the global `SGcontext`. This function ensures the shader resource is properly stored and accessible for rendering operations.

**Parameters**:
- `SGhandle* handle`: A pointer to the handle containing the shader data to be stored.

**Returns**: `void`

<br>
<br>

```c
void sgStoreTexture(SGhandle* handle)
```
**Description**: 
Stores the texture data associated with the provided handle into the global `SGcontext`. This function ensures the texture resource is properly stored and accessible for rendering operations.

**Parameters**:
- `SGhandle* handle`: A pointer to the handle containing the texture data to be stored.

**Returns**: `void`

<br>
<br>

```c
void sgStoreUniform(SGhandle* handle)
```
**Description**: 
Stores the uniform data associated with the provided handle into the global `SGcontext`. This function ensures the uniform resource is properly stored and accessible for rendering operations.

**Parameters**:
- `SGhandle* handle`: A pointer to the handle containing the uniform data to be stored.

**Returns**: `void`

<br>
<br>

## - ctx/render.h
```c
void sgGetRenderModeStr(char* str)
```
**Description**: 
Retrieves the current rendering mode as a string and stores it in the provided buffer.

**Parameters**:
- `char* str`: A pointer to a buffer where the rendering mode string will be stored.

**Returns**: `void`

<br>
<br>

```c
void sgBeginRender(u32 mode)
```
**Description**: 
Begins the rendering process by setting the render mode and clearing the color and depth buffers.

**Parameters**:
- `u32 mode`: The rendering mode to set (e.g., `SG_LINES`, `SG_QUADS`, `SG_TRIANGLES`).

**Returns**: `void`

<br>
<br>

```c
SGdrawcall* sgDrawCall(const SGhandle* mhandle, const SGhandle* thandle, const SGhandle* shandle, const SGhandle* uniforms, u32 nuniforms)
```
**Description**: 
Generates a draw call structure for rendering based on the provided mesh, texture, shader, and uniform handles. This function configures the draw call with the necessary data for rendering.

**Parameters**:
- `const SGhandle* mhandle`: A pointer to the mesh handle.
- `const SGhandle* thandle`: A pointer to the texture handle.
- `const SGhandle* shandle`: A pointer to the shader handle.
- `const SGhandle* uniforms`: A pointer to an array of uniform handles.
- `u32 nuniforms`: The number of uniforms in the array.

**Returns**: 
- `SGdrawcall*`: A pointer to the generated draw call structure.

<br>
<br>

```c
void sgClearColor(f32 r, f32 g, f32 b, f32 a)
```
**Description**: 
Sets the clear color for the rendering context.

**Parameters**:
- `f32 r`: Red component of the clear color.
- `f32 g`: Green component of the clear color.
- `f32 b`: Blue component of the clear color.
- `f32 a`: Alpha component of the clear color.

**Returns**: `void`
<br>
<br>

```c
void sgRender(SGdrawcall* call)
```
**Description**: 
Renders a draw call by binding the necessary resources and executing the draw command.

**Parameters**:
- `SGdrawcall* call`: A pointer to the draw call structure containing the rendering data.

**Returns**: `void`
<br>
<br>

```c
void sgEndRender(void* window)
```
**Description**: 
Ends the rendering process by swapping the buffers and unbinding the draw call from the rendering context.

**Parameters**:
- `void* window`: A pointer to the window where the rendering is being displayed.

**Returns**: `void`
<br>
<br>

