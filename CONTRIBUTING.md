# Contributing to R-Type

Thank you for considering contributing to the R-Type project! This document outlines the process for submitting code and other changes. Please follow these guidelines to ensure smooth collaboration.

## Pull Requests (PRs)

- All pull requests must reference an issue and be prefixed with `RTP-XX`, where `XX` is the issue number.
- Ensure that the title of your pull request is clear and follows the format: `RTP-XX: [Description of the change]`.
- Link the relevant issue in the body of the pull request.

## Commit Messages

We use the [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/) standard for commit messages. Please ensure your commit messages follow this format:

```
<type>(<scope>): <description>

[optional body]

[optional footer(s)]
```

Examples:
- `feat(client): add player movement feature`
- `fix(server): resolve crash on connection timeout`

Common commit types:
- `feat`: A new feature
- `fix`: A bug fix
- `docs`: Documentation only changes
- `style`: Changes that do not affect the meaning of the code (white-space, formatting, missing semi-colons, etc)
- `refactor`: A code change that neither fixes a bug nor adds a feature
- `test`: Adding missing tests or correcting existing tests
- `chore`: Changes to the build process or auxiliary tools and libraries such as documentation generation

## Code Formatting and Linting

The code must conform to the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html). We enforce this style using `clang-format` and `cpplint`. Please ensure that your code passes the following checks before submitting:

- Run `make format` to format all `.cpp`, `.tpp` and `.hpp` files.
- Run `make lint` to check for any linting issues.

You can install these tools locally or run them via [our provided Docker environment](./ci/style.dockerfile).

## Running Tests

Please ensure all tests pass before submitting your pull request. You can run the tests using:

```bash
make test_run
```

For new features or bug fixes, include corresponding unit tests to verify the changes.

## Questions

If you have any questions about contributing, feel free to open an issue or reach out to the maintainers.

Thank you for contributing to R-Type!
```
