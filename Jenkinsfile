BINARIES=[
    'client': 'r-type_client',
    'server': 'r-type_server'
]
TESTS=[
    'client': 'r-type_client_tests',
    'server': 'r_type_server_tests'
]

pipeline {
    agent any
    options {
        skipDefaultCheckout(true)
    }

    stages {
        stage ('Checkout') {
            steps {
                cleanWs()
                checkout scm
            }
        }

        stage ('Pull request') {
            when {
                not {
                    branch 'main'
                }
            }

            parallel {
                stage ('Linux environment') {
                    agent {
                        dockerfile {
                            filename 'ci/unix.dockerfile'
                            reuseNode true
                        }
                    }
                    stages {
                        stage ('Generate build files') {
                            steps {
                                script {
                                    sh 'cmake --preset=unix:release'
                                }
                            }
                        }
                        stage ('Build') {
                            matrix {
                                axes {
                                    axis {
                                        name 'TARGET_KEY'
                                        values 'client', 'server'
                                    }
                                }
                            }
                            steps {
                                dir('build/unix/release') {
                                    stages {
                                        stage('Building "${BINARIES[env.TARGET_KEY]}"') {
                                            steps {
                                                sh 'cmake --build . --target ${BINARIES[env.TARGET_KEY]} -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=$PWD/bin'
                                            }
                                        }
                                        stage('Looking for "${BINARIES[env.TARGET_KEY]}"') {
                                            steps {
                                                script {
                                                    if (!fileExists("bin/${BINARIES[env.TARGET_KEY]}")) {
                                                        error "Binary ${BINARIES[env.TARGET_KEY]} not found"
                                                    } else if (sh(script: "test -x bin/${BINARIES[env.TARGET_KEY]}", returnStatus: true) != 0) {
                                                        error "Binary ${BINARIES[env.TARGET_KEY]} is not executable"
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
        }
    }
}
