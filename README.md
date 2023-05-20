# View

Submodule for non specific Qt Widgets.

## Testing

The Test directory is setup to work with [googletest](https://github.com/google/googletest).

## Building

Building with CMake and Make.

```sh
mkdir build
cd build
cmake .. -DView_BUILD_TEST=ON -DView_AUTO_RUN_TEST=ON
make
```

### Optional defines

| Option                  | Description                                          | Default |
| :---------------------- | :--------------------------------------------------- | :-----: |
| View_BUILD_TEST         | Build the unit test program.                         |   ON    |
| View_AUTO_RUN_TEST      | Automatically run the test program.                  |   OFF   |
| View_USE_STATIC_RUNTIME | Build with the MultiThreaded(Debug) runtime library. |   ON    |
