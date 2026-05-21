Pod::Spec.new do |s|
  s.name             = 'react-native-privyx-crypto'
  s.version          = '0.1.0'
  s.summary          = 'Post-quantum crypto native module for React Native'
  s.authors          = { 'Privyx' => 'dev@privyx.network' }
  s.homepage         = 'https://privyx.network'
  s.source           = { :path => '..' }
  s.license          = { :type => 'MIT' }
  s.source_files     = 'PrivyxCrypto.mm'

  s.vendored_libraries = '../libs/ios/PrivyxCryptoFFI.xcframework/ios-arm64_x86_64-simulator/libprivyx-sim.a', '../libs/ios/PrivyxCryptoFFI.xcframework/ios-arm64/libprivyx.a'

  s.pod_target_xcconfig = {
    'HEADER_SEARCH_PATHS' => '"${PODS_ROOT}/../../sdk_privyx/libs/ios/PrivyxCryptoFFI.xcframework/ios-arm64_x86_64-simulator/Headers"',
    'LIBRARY_SEARCH_PATHS' => '"${PODS_ROOT}/../../sdk_privyx/libs/ios/PrivyxCryptoFFI.xcframework/ios-arm64_x86_64-simulator"',
    'OTHER_LDFLAGS' => '-lprivyx-sim'
  }

  s.user_target_xcconfig = {
    'LIBRARY_SEARCH_PATHS' => '"${PODS_ROOT}/../../sdk_privyx/libs/ios/PrivyxCryptoFFI.xcframework/ios-arm64_x86_64-simulator"',
    'OTHER_LDFLAGS' => '-lprivyx-sim'
  }

  s.dependency 'React-Core'
end
