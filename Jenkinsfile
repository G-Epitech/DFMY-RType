PROJECTS = ['client', 'server']
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

                        stage('Projects') {
                            steps {
                                script {
                                    for (project in PROJECTS) {
                                        def TARGET_BINARY = BINARIES[project]
                                        def TARGET_TEST = TESTS[project]

                                        stage ("Build ${project}") {
                                            bat "cmake --build build/windows/release --target ${TARGET_BINARY}"
                                            script {
                                                if (fileExists("/bin/${TARGET_BINARY}.exe")) {
                                                    error "Binary ${TARGET_BINARY}.exe not found"
                                                }
                                            }
                                        }

                                        stage ("Tests ${project}") {
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
