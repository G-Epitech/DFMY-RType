pipeline {
    agent any
    options {
        skipDefaultCheckout(true)
    }

    environment {
        RTYPE_BINARIES_LIST = 'r-type_server r-type_client'
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
                                    sh 'cmake -B build --toolchain=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release'
                                    sh 'cmake --build build'
                                    dir('build') {
                                        def binaries = env.RTYPE_BINARIES_LIST.split(' ')
                                        for (binary in binaries) {
                                            if (!fileExists(binary)) {
                                                error "Binary ${binary} not found"
                                            } else if (!isExecutable(binary)) {
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