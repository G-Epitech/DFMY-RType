BINARIES = [
    'client': 'r-type_client',
    'server': 'r-type_server'
]
TESTS = [
    'client': 'r-type_client_tests',
    'server': 'r-type_server_tests'
]

pipeline {
    agent any
    options {
        skipDefaultCheckout(true)
    }

    stages {
        stage('Checkout') {
            steps {
                cleanWs()
                checkout scm
            }
        }

        stage('Pull request') {
            when {
                not {
                    branch 'main'
                }
            }
            stages {
                /*stage('Linux environment') {
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
                        stage('Projects') {
                            matrix {
                                axes {
                                    axis {
                                        name 'TARGET_KEY'
                                        values 'client', 'server'
                                    }
                                }
                                environment {
                                    TARGET_BINARY = "${BINARIES[TARGET_KEY]}"
                                    TARGET_TEST = "${TESTS[TARGET_KEY]}"
                                }
                                stages {
                                    stage('Build') {
                                        steps {
                                            sh 'cmake --build build/unix/release --target ${TARGET_BINARY}'
                                            script {
                                                if (!fileExists("bin/${env.TARGET_BINARY}")) {
                                                    error "Binary ${env.TARGET_BINARY} not found"
                                                } else if (sh(script: "test -x bin/${TARGET_BINARY}", returnStatus: true) != 0) {
                                                    error "Binary ${env.TARGET_BINARY} is not executable"
                                                }
                                            }
                                        }
                                    }

                                    stage('Tests') {
                                        steps {
                                            sh 'cmake --build build/unix/release --target ${TARGET_TEST}'
                                            sh './bin/${TARGET_TEST}'
                                        }
                                    }
                                }
                            }
                        }
                    }
                } */

                stage('Windows environment') {
                    agent {
                        label 'windows'
                    }
                    stages {
/*                         stage('Checkout') {
                            steps {
                                cleanWs()
                                checkout scm
                            }
                        }

                        stage('Generate build files') {
                            steps {
                                script {
                                    bat 'cmake --preset=windows:release -DCMAKE_RUNTIME_OUTPUT_DIRECTORY="$PWD/bin"'
                                }
                            }
                        } */

                        stage('Projects') {
                            matrix {
                                axes {
                                    axis {
                                        name 'TARGET_KEY'
                                        values 'client', 'server'
                                    }
                                }
                                environment {
                                    TARGET_BINARY = "${BINARIES[TARGET_KEY]}"
                                    TARGET_TEST = "${TESTS[TARGET_KEY]}"
                                }
                                stages {
                                    stage('Build') {
                                        steps {
                                            bat 'echo $TARGET_BINARY'
                                            /* bat 'cmake --build build/windows/release --target "$TARGET_BINARY"'
                                            script {
                                                if (!fileExists("bin/${env.TARGET_BINARY}.exe")) {
                                                    error "Binary ${env.TARGET_BINARY}.exe not found"
                                                }
                                            } */
                                        }
                                    }

                                    /* stage('Tests') {
                                        steps {
                                            bat 'cmake --build build/windows/release --target "$TARGET_BINARY"'
                                            bat './bin/"$TARGET_BINARY".exe'
                                        }
                                    } */
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
