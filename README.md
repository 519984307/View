# View

Submodule for non specific Qt Widgets.

## Testing

The Test directory is setup to work with [googletest](https://github.com/google/googletest).

## Building

![A1](https://github.com/i1qh2n/View/actions/workflows/build-linux.yml/badge.svg)
![A2](https://github.com/i1qh2n/View/actions/workflows/build-windows.yml/badge.svg)

```sh
mkdir Build
cmake -S . -B Build -DView_BUILD_TEST=ON -DView_AUTO_RUN_TEST=ON
cmake --build Build
```

### Optional defines

| Option                  | Description                                          | Default |
| :---------------------- | :--------------------------------------------------- | :-----: |
| View_BUILD_TEST         | Build the unit test program.                         |   ON    |
| View_AUTO_RUN_TEST      | Automatically run the test program.                  |   OFF   |

# Dependencies 

### Dependencies

Local and external dependencies.

```mermaid
graph BT;
      View-->Utils;
      View-->Qt;

      Qt-->Core;
      Qt-->Gui;
      Qt-->Widgets;
```
