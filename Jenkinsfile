BINARIES = ['client', 'server']
BINARIES_TARGETS = [
    'client': 'r-type_client',
    'server': 'r-type_server',
]
BINARIES_TESTS = [
    'client': 'r-type_client_tests',
    'server': 'r-type_server_tests'
]
LIBS = ['network-sdk', 'ECS-sdk']
LIBS_TARGETS = [
    'network-sdk': [
        'target': 'r-type_network_sdk',
        'type': 'shared'
    ],
    'ECS-sdk': [
        'target': 'r-type_ECS_sdk',
        'type': 'shared'
    ]
]
LIBS_TESTS = [
    'network-sdk': 'r-type_network_sdk_tests',
    'ECS-sdk': 'r-type_ECS_sdk_tests'
]

pipeline {
    agent any
    stages {
        stage ('Check style') {
            parallel {

                stage ('Lint') {
                    agent {
                        dockerfile {
                            filename 'ci/style.dockerfile'
                        }
                    }

                    steps {
                        sh 'make lint'
                    }
                }

                stage ('Format') {
                    agent {
                        dockerfile {
                            filename 'ci/style.dockerfile'
                        }
                    }
                    steps {
                        sh 'make format-check'
                    }
                }
            }
        }

        stage ('Build and tests') {
            parallel {
                stage('Linux environment') {
                    agent {
                        dockerfile {
                            filename 'ci/unix.dockerfile'
                            reuseNode true
                        }
                    }

                    stages {
                        stage('Generate build files') {
                            steps {
                                script {
                                    sh 'cmake --preset=unix:release -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=$PWD/bin'
                                }
                            }
                        }

                        stage('Project binaries') {
                            steps {
                                script {
                                    for (binary in BINARIES) {
                                        def TARGET_BINARY = BINARIES_TARGETS[binary]
                                        def TARGET_TEST = BINARIES_TESTS[binary]

                                        stage ("Build and test ${binary}") {
                                            sh "cmake --build build/unix/release --target ${TARGET_BINARY}"
                                            fileExists("bin/${TARGET_BINARY}")
                                            sh "cmake --build build/unix/release --target ${TARGET_TEST}"
                                            sh "bin/${TARGET_TEST}"
                                        }
                                    }
                                }
                            }
                        }

                        stage('Project libraries') {
                            steps {
                                script {
                                    for (lib in LIBS) {
                                        def TARGET_LIB = LIBS_TARGETS[lib]['target']
                                        def TARGET_LIB_EXT = LIBS_TARGETS[lib]['type'] == 'shared' ? 'so' : 'a'
                                        def TARGET_TEST = LIBS_TESTS[lib]

                                        stage ("Build and test ${lib}") {
                                            sh "cmake --build build/unix/release --target ${TARGET_LIB}"
                                            fileExists("bin/${TARGET_LIB}.${TARGET_LIB_EXT}")
                                            sh "cmake --build build/unix/release --target ${TARGET_TEST}"
                                            sh "bin/${TARGET_TEST}"
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                stage('Windows environment') {
                    agent {
                        label 'windows'
                    }

                    stages {
                        stage('Checkout') {
                            steps {
                                checkout scm
                            }
                        }

                        stage('Generate build files') {
                            steps {
                                script {
                                    bat 'cmake --preset=windows:release -DCMAKE_RUNTIME_OUTPUT_DIRECTORY="%cd%\\bin"'
                                }
                            }
                        }

                        stage('Project binaries') {
                            steps {
                                script {
                                    for (binary in BINARIES) {
                                        def TARGET_BINARY = BINARIES_TARGETS[binary]
                                        def TARGET_TEST = BINARIES_TESTS[binary]

                                        stage ("Build and test ${binary}") {
                                            bat "cmake --build build/windows/release --target ${TARGET_BINARY}"
                                            fileExists("bin/${TARGET_BINARY}.exe")
                                            bat "cmake --build build/windows/release --target ${TARGET_TEST}"
                                            bat "bin\\${TARGET_TEST}.exe"
                                        }
                                    }
                                }
                            }
                        }

                        stage('Project libraries') {
                            steps {
                                script {
                                    for (lib in LIBS) {
                                        def TARGET_LIB = LIBS_TARGETS[lib]['target']
                                        def TARGET_LIB_EXT = LIBS_TARGETS[lib]['type'] == 'shared' ? 'dll' : 'lib'
                                        def TARGET_TEST = LIBS_TESTS[lib]

                                        stage ("Build and test ${lib}") {
                                            bat "cmake --build build/windows/release --target ${TARGET_LIB}"
                                            fileExists("bin/${TARGET_LIB}.${TARGET_LIB_EXT}")
                                            bat "cmake --build build/windows/release --target ${TARGET_TEST}"
                                            bat "bin\\${TARGET_TEST}.exe"
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
