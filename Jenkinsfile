pipeline {
    agent any
    options {
        skipDefaultCheckout(true)
    }

    environment {
        RTYPE_BINARIES_LIST = 'server/r-type_server client/r-type_client'
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
            stages {
                stage ('Build') {
                    parallel {
                        stage ('Linux environment') {
                            agent {
                                dockerfile {
                                    filename 'unix.dockerfile'
                                    reuseNode true
                                }
                            }
                            steps {
                                script {
                                    sh 'cmake --preset=unix:release'
                                    sh 'cmake --build build/unix/release'
                                    dir('build/unix/release') {
                                        def binaries = env.RTYPE_BINARIES_LIST.split(' ')
                                        for (binary in binaries) {
                                            if (!fileExists(binary)) {
                                                error "Binary ${binary} not found"
                                            } else if (sh(script: "test -x ${binary}", returnStatus: true) != 0) {
                                                error "Binary ${binary} is not executable"
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
