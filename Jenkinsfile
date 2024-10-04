BINARIES = ['client', 'server']
BINARIES_TARGETS = [
    'client': 'r-type_client',
    'server': 'r-type_server',
]
BINARIES_TESTS = [
    'client': 'r-type_client_tests',
    'server': 'r-type_server_tests'
]
LIBS = ['abra', 'ECS']
LIBS_TARGETS = [
    'abra': [
        'target': 'abra',
        'type': 'shared'
    ],
    'ECS': [
        'target': 'r-type_ECS_sdk',
        'type': 'shared'
    ]
]
LIBS_TESTS = [
    'abra': 'abra_tests',
    'ECS': 'r-type_ECS_sdk_tests'
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
                /*
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
                */

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
                                    bat 'cmake --preset=windows:release'
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
                                            bat "cmake --build build/windows/release --config release --target ${TARGET_LIB}"
                                            fileExists("build/windows/release/libs/${lib}/${TARGET_LIB}.${TARGET_LIB_EXT}")
                                            bat "cmake --build build/windows/release --config release --target ${TARGET_TEST}"
                                            bat "xcopy build\\windows\\release\\libs\\${lib}\\*.dll build\\windows\\release\\libs\\${lib}\\tests /Y"
                                            bat "build\\windows\\release\\libs\\${lib}\\tests\\${TARGET_TEST}.exe"
                                        }
                                    }
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
                                            bat "cmake --build build/windows/release --config release --target ${TARGET_BINARY}"
                                            fileExists("build/windows/release/bin/${binary}/${TARGET_BINARY}.exe")
                                            bat "cmake --build build/windows/release --config release --target ${TARGET_TEST}"
                                            bat "xcopy build\\windows\\release\\${binary}\\*.dll build\\windows\\release\\${binary}\\tests /Y"
                                            bat "build\\windows\\release\\${binary}\\tests\\${TARGET_TEST}.exe"
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        stage ('Create Release') {
            when {
                allOf {
                    buildingTag()
                    /* branch 'main' */
                }
            }
            steps {
                script {
                    VERSION = sh(script: 'git describe --tags --abbrev=0', returnStdout: true).trim().substring(1)
                    echo "NEW VERSION IS $VERSION"
                }
                script {
                    withCredentials([usernamePassword(credentialsId: '097d37a7-4a1b-4fc6-ba70-e13f043b70e8',
                                                      usernameVariable: 'GITHUB_APP',
                                                      passwordVariable: 'GITHUB_ACCESS_TOKEN')]) {
                        echo "Tag: $VERSION"
                        def response = sh(script: """
                            curl -X POST -H "Content-Type: application/json" \
                                 -H "Authorization: Bearer \$GITHUB_ACCESS_TOKEN" \
                                 -d '{ "tag_name": "$VERSION", \
                                       "name": "Release $VERSION", \
                                       "body": "Description of the release.", \
                                       "draft": false, \
                                       "prerelease": false }' \
                                 https://api.github.com/repos/G-Epitech/DFMY-RType/releases
                        """, returnStdout: true)

                        def jsonResponse = readJSON(text: response)
                        echo "Response: ${response}"
                        def releaseId = jsonResponse.id

                        echo "Release ID: ${releaseId}"
                        if (releaseId) {
                            echo "Release created successfully"
                            RELEASE_ID = releaseId
                            ACCESS_TOKEN = GITHUB_ACCESS_TOKEN
                            def responsetwo = bat(script: """
                                curl -L \
                                    -X POST \
                                    -H "Accept: application/vnd.github+json" \
                                    -H "Authorization: Bearer \$ACCESS_TOKEN" \
                                    -H "Content-Type: application/octet-stream" \
                                    "https://uploads.github.com/repos/G-Epitech/DFMY-RType/releases/${RELEASE_ID}/assets?name=${filename}" \
                                    --data-binary "@build/windows/release/${filename}"
                            """, returnStdout: true)
                            echo "Response: ${responsetwo}"
                        } else {
                            echo "Failed to create release, it may already exist"
                        }
                    }
                }
            }
        }

        stage ('Publish') {
            when {
                allOf {
                    buildingTag()
                    expression {
                        RELEASE_ID != null
                    }
                    /* branch 'main' */
                }
            }
            parallel {
                stage ('Windows Environment') {
                    agent {
                        label 'windows'
                    }

                    stages {
                        stage('Echo Version') {
                            steps {
                                echo "Version: $VERSION"
                                echo "Release ID: $RELEASE_ID"
                            }
                        }

                        stage('Generate installers') {
                            steps {
                                script {
                                    for (binary in BINARIES) {
                                        def TARGET_BINARY = BINARIES_TARGETS[binary]

                                        stage ("${binary}") {
                                            bat "cmake --preset=windows:release:${binary}"
                                            bat "cmake --build build/windows/release --config release --target r-type_${binary}"
                                            bat "cd build/windows/release && cpack -C release"
                                        }
                                    }
                                }
                            }
                        }

                        stage('Upload artifacts') {
                            steps {
                                script {
                                    for (binary in BINARIES) {
                                        def filename = "R-Type-${binary}-${VERSION}.zip"
                                        echo "Uploading ${filename}"
                                        if (ACCESS_TOKEN) {
                                            echo "Access Token"
                                        }
                                        def response = bat(script: """
                                            curl -L \
                                                -X POST \
                                                -H "Accept: application/vnd.github+json" \
                                                -H "Authorization: Bearer \$ACCESS_TOKEN" \
                                                -H "Content-Type: application/octet-stream" \
                                                "https://uploads.github.com/repos/G-Epitech/DFMY-RType/releases/${RELEASE_ID}/assets?name=${filename}" \
                                                --data-binary "@build/windows/release/${filename}"
                                        """, returnStdout: true)
                                        echo "Response: ${response}"
                                        def jsonResponse = readJSON(text: response)
                                        echo "Upload URL: ${jsonResponse.url}"
                                        def status = jsonResponse.state
                                        echo "Upload status: ${status}"
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
