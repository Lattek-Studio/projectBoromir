import { CapacitorConfig } from '@capacitor/cli';

const config: CapacitorConfig = {
  appId: 'org.lattek.dust',
  appName: 'LattekDust',
  webDir: 'build',
  server: {
    androidScheme: 'https'
  },
  plugins: {
    StatusBar: {
      // style: 'light',
      overlay: true
    }
  }
};

export default config;
